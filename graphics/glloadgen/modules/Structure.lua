
local util = require "util"
local TabbedFile = require "TabbedFile"

--[[
Directory of used context names:

- style
- spec
- specData
- options
- basename
- hFile			Provided by file blocks
- extName		Provided by extension iterators.
- version		Provided by version iterators.
- sub_version	Provided by sub-version iterators.
- enum			Provided by enum iterators.
- enumTable		Provided by enum iterators.
- enumSeen		Provided by enum seen blocks.
- func			Provided by function iterators.
- typemap		Provided by function iterators.
- funcSeen		Provided by func seen blocks.

Structure actions:

- file: Creates a TabbedFile.
-		name: The style function to call. It should return a filename. The defualt parameters are (basename, options)

- block: Represents a block. Must be in a file scope.
-		name: Part of the function name to call. When starting the block, it will call "WriteBlockBegin"..name. To end it, it will call "WriteBlockEnd"..name. The default parameters are (hFile, spec, options).

- group: Represents a collection of stuff. Has no particular semantics (though it can have conditionals and such.

- write: Simply calls a given writing function. Must be in a file scope.
-		name: Part of the function name to call. The complete function name is "Write"..name. The default parameters are (hFile, specData, spec, options).

- blank: Writes an empty line. Must be in a file scope.

- filter: Contains a group of actions. If the named function returns false, then the children will not be processed.
-		name: Part of the function name to call. The complete function name is "Filter"..name. The default parameters are () (ie: none).

- ext-iter: Iterates over all of the extensions explicitly requested by the user. Cannot nest. Children can access the `extName` parameter, the name of the current extension.

- version-iter: Iterates over each version in the spec, which is less than or equal to the requested version, where applicable. Cannot nest. Children can access the `version` parameter, the current version as a *string*.

- sub-version-iter: Iterates over each version that is less than or equal to the current version. Cannot nest. Must be done within a context that provides the `version` parameter. Children can access the `sub_version` parameter, the current sub-version as a *string*.

- core-ext-iter: Iterates over all core extensions of the current version. Cannot nest. Must be done within a context that provides the `version` parameter. Children can access the `extName` parameter, the name of the current core extension.

- core-ext-cull-iter: Iterates over all core extensions that were *not* explicitly asked for. Cannot nest. Must be done within a context that provides the `version` parameter. Children can access the `extName` parameter, the name of the current core extension.

- enum-seen: Children can access the `enumSeen` parameter. This is a mapping between enumerator names and where that enumerator was first seen. If it is not in this list, then this enumerator was not processed before (within the scope of the `enum-seen`). The `enum-iter` works in tandem with this to keep the `enumSeen` table up-to-date. The value for an enum may be an extension name or a core version number.

- enum-iter: Iterates over all of the enumerators within scope. The "scope" is defined by whether `extName` or `version` is available. So if `extName` is available, then it iterates over all enums within that extension. If `version` is available, then it iterates over enums within *just* that version (the options.profile also applies). If both are visible, `extName` wins. Children can access the `enum` and `enumTable` parameters, which are the current enum and a name-table of all enums in the system. The latter is used to determine the value of the enum.

- func-seen: Children can access the `funcSeen` parameter. This works like `enum-seen` but for functions and `func-iter`.

- func-iter: Iterates over all of the functions within scope, using the same scoping rules as `enum-iter`. Children can access the `func` and `typemap` parameters, which are the current function and a typemap used to compute parameters and return-values (primarily for C).

Common properties:

- name: The name of a function to call, or part of a name. This can also include a parenthesized list of parameters. The parameter names much match those in the above list of parameters, and those parameters must be available in this particular scope (different actions create different scopes. If a particular parameter is not available in a context, a runtime error will occur.

- style: This represents a scoping for the style for all children of this action. It will access the main style using the given string, and it expects a table of functions. All names within this action will be expected to be in that style; if they are not, they'll check the previous style, on down until the first style. These can be nested, but note that the fetching of the table is always done in the *main* style, not the "current" style.

- first: When set, this particular action (and any of its child actions) will only be executed the first time through the most recent iteration loop. Note that this only works for the most recent iteration loop. And it only works within an interation loop, since they are the only ones who execute their children multiple times.

- last: Like first, except for the last time through a block. Usually for inserting blank space.

- cond: Only processes the node and its children if the condition is "true". Available conditions:
	- ext-iter
	- version-iter
	- core-ext-iter
	- core-ext-cull-iter
	- enum-iter
	- func-iter
	- core-funcs: True if the spec has core functions. IE: is OpenGL.

All of the iterator-based conditions will be true iff performing that iterator in this context would result in at least one match. They can only be used in the same context where the equivalent iterator could.

]]

local actionTypes = {}
local conditionals = {}

-------------------------------
-- Action base-class
local action = {}

function action:Process(context)
	--Allow start-of-iteration only data to parse.
	if(self.first) then
		--Note that it's *specifically* equal to false. Being 'nil' isn't enough.
		if(context._first == false) then
			return
		end
	end
	
	--Allow end-if-iteration only data to parse.
	if(self.last) then
		--Note that it's *specifically* equal to false. Being 'nil' isn't enough.
		if(context._last == false) then
			return
		end
	end
	
	--Conditional
	if(self._cond) then
		if(not conditionals[self._cond](context)) then
			return
		end
	end
	
	--NO MORE RETURNS FROM THIS POINT FORWARD!
	if(self.newStyle) then
		context:PushStyle(self.newStyle)
	end
	
	local noChildren = nil
	if(self.PreProcess) then
		noChildren = self:PreProcess(context)
	end

	if(not noChildren) then
		self:ProcessChildren(context)
	end

	if(self.PostProcess) then
		self:PostProcess(context)
	end
	
	if(self.newStyle) then
		context:PopStyle()
	end
end

function action:ProcessChildren(context)
	for _, action in ipairs(self) do
		--Preserve the first value.
		local oldFirst = context._first
		local oldLast = context._last
		action:Process(context)
		context._first = oldFirst
		context._last = oldLast
	end
end

function action:CallFunction(context, name)
	name = name or self.name
	self:Assert(name, "Unknown function name.")
	local style = context:FindStyleForFunc(name)
	self:Assert(style, "The style does not have a function " .. name)
	
	local paramList = {}
	for _, param in ipairs(self.params) do
		assert(context[param], "The function " .. name ..
			" need a parameter " .. param .. " which doesn't exist at this point")
		paramList[#paramList + 1] = context[param]
	end
	
	return style[name](unpack(paramList))
end

function action:Assert(test, text)
	assert(test, self._actionType .. ": " .. text)
end

--Iterates over the list, setting the second element returned from the iterator
--as the given context table key.
function action:IterateChildren(context, list, key, PostProc)
	PostProc = PostProc or function() end
	
	local oldVal = context[key]
	for _, val in ipairs(list) do
		context[key] = val
		context._first = (_ == 1)
		context._last = (_ == #list)
		self:ProcessChildren(context)
		PostProc(context, val)
	end
	context[key] = oldVal
end

local function CreateAction(data, actionType)
	local act = {}
	util.DeepCopyTable(action, act)
	
	assert(actionType, "No name given for action type")
	
	--Create custom param list.
	if(data.name) then
		local name, params = data.name:match("([_%w]+)%s*%((.*)%)")
		if(name) then
			local paramList = {}
			for param in params:gmatch("([_%a][_%w]*)") do
				paramList[#paramList + 1] = param
			end
			params = paramList
		else
			name = data.name
		end
		
		act.name = name
		act.params = params
	end
	
	if(data.cond) then
		assert(conditionals[data.cond], "Unknown conditional " .. data.cond)
		act._cond = data.cond
	end
	
	act.newStyle = data.style

	--Make child actions recursively.
	for _, child in ipairs(data) do
		assert(actionTypes[child.type], "Unknown command type " .. child.type)
		act[#act + 1] = actionTypes[child.type](child)
	end
	
	if(data.first) then
		act.first = true
	end
	
	if(data.last) then
		act.last = true
	end
	
	act._actionType = actionType
	
	return act
end

local function MakeActionType(typeName, typeTable, PostInitFunc)
	actionTypes[typeName] = function(data)
		local act = CreateAction(data, typeName)
		util.DeepCopyTable(typeTable, act)
		
		PostInitFunc(act, data)
		
		return act
	end
end


----------------------------
-- File Action
local fileAction = {}

function fileAction:PreProcess(context)
	assert(context.hFile == nil, "You cannot nest `file` blocks.")

	local filename = self:CallFunction(context)
	
	context.hFile = util.CreateFile(filename, context.options.indent)
end

function fileAction:PostProcess(context)
	context.hFile:close()
	context.hFile = nil
end

MakeActionType("file", fileAction, function(self, data)
	assert(data.style, "File actions must have a `style`")
	assert(data.name, "File actions need a name to call.")

	self.params = self.params or {"basename", "options"}
end)


-------------------------------------
-- Block Action
local blockAction = {}

function blockAction:PreProcess(context)
	assert(context.hFile, "Cannot write a block outside of a file. " .. self.name)
	self:CallFunction(context, "WriteBlockBegin" .. self.name)
end

function blockAction:PostProcess(context)
	self:CallFunction(context, "WriteBlockEnd" .. self.name)
end

MakeActionType("block", blockAction, function(self, data)
	assert(data.name, "Block actions must have a `name`")

	self.params = self.params or {"hFile", "spec", "options"}
end)


-------------------------------------
-- Group Action
local groupAction = {}

MakeActionType("group", groupAction, function(self, data)
end)


------------------------------------------
-- Write Action
local writeAction = {}

function writeAction:PreProcess(context)
	assert(context.hFile, "Cannot write data outside of a file.")
	self:CallFunction(context)
end

MakeActionType("write", writeAction, function(self, data)
	assert(data.name, "Write actions must have a `name`")
	self.name = "Write" .. self.name
	self.params = self.params or {"hFile", "specData", "spec", "options"}
end)


------------------------------------------
-- Blank Action
local blankAction = {}

function blankAction:PreProcess(context)
	self:Assert(context.hFile, "Blanks must be in files.")
	context.hFile:write("\n")
end

MakeActionType("blank", blankAction, function(self, data)
end)


-------------------------------------------
-- Filter Action
local filterAction = {}

function filterAction:PreProcess(context)
	local shouldFilter = self:CallFunction(context, self.name)
	if(self.neg) then
		shouldFilter = not shouldFilter
	end
	return not shouldFilter
end

MakeActionType("filter", filterAction, function(self, data)
	assert(data.name, "Filter actions must have a `name`")
	self.name = "Filter" .. self.name
	self.neg = data.neg
	self.params = self.params or {}
end)


---------------------------------------------
-- Extension Iterator Action
local extIterAction = {}

function extIterAction:PreProcess(context)
	self:Assert(context.extName == nil, "Cannot nest ext-iter actions.")
	self:IterateChildren(context, context.options.extensions, "extName")
	return true --Stops regular child processing.
end

MakeActionType("ext-iter", extIterAction, function(self, data)
end)

conditionals["ext-iter"] = function(context)
	return #context.options.extensions ~= 0
end


-----------------------------------------------
-- Version Iterator
local versionIterAction = {}

function versionIterAction:PreProcess(context)
	self:Assert(context.version == nil, "Cannot nest version-iter actions.")
	local rawVersionList = context.spec.GetVersions()
	local versionList = {}
	for _, version in ipairs(rawVersionList) do
		if(tonumber(version) <= tonumber(context.options.version)) then
			versionList[#versionList + 1] = version
		end
	end

	self:IterateChildren(context, versionList, "version")
	return true --Stops regular child processing.
end

MakeActionType("version-iter", versionIterAction, function(self, data)
end)

conditionals["version-iter"] = function(context)
	return #context.spec.GetVersions() ~= 0
end


-----------------------------------------------
-- Sub-Version Iterator
local subVersionIterAction = {}

function subVersionIterAction:PreProcess(context)
	self:Assert(context.sub_version == nil, "Cannot nest sub-version-iter actions.")
	self:Assert(context.version, "Must put sub-version-iter inside versions.")
	local rawVersionList = context.spec.GetVersions()
	local versionList = {}
	for _, version in ipairs(rawVersionList) do
		if(tonumber(version) <= tonumber(context.version)) then
			versionList[#versionList + 1] = version
		end
	end

	self:IterateChildren(context, versionList, "sub_version")
	return true --Stops regular child processing.
end

MakeActionType("sub-version-iter", subVersionIterAction, function(self, data)
end)


---------------------------------------------
-- Core Extension Iterator Action
local coreExtIterAction = {}

function coreExtIterAction:PreProcess(context)
	self:Assert(context.version, "Must put this in a version iterator")
	self:Assert(context.extName == nil, "Cannot nest core-ext-iter actions.")
	local coreExts = context._coreExts
	if(coreExts[context.version]) then
		self:IterateChildren(context, coreExts[context.version], "extName")
	end
	return true --Stops regular child processing.
end

MakeActionType("core-ext-iter", coreExtIterAction, function(self, data)
end)

conditionals["core-ext-iter"] = function(context)
	assert(context.version, "Cannot have a core-ext-iter conditional outside of a version.")
	return context._coreExts[context.version] ~= nil
end


---------------------------------------------
-- Core Extension Iterator Action, culled against the requested extensions.
local coreExtCullIterAction = {}

local function BuildCulledExtList(context)
	local coreExts = context._coreExts
	if(coreExts[context.version]) then
		local extList = {}
		for _, ext in ipairs(coreExts[context.version]) do
			if(not context._extTbl[ext]) then
				extList[#extList + 1] = ext
			end
		end
		return extList
	else
		return {}
	end
end

function coreExtCullIterAction:PreProcess(context)
	self:Assert(context.version, "Must put core-ext-cull-iters in a version")
	self:Assert(context.extName == nil, "Cannot nest core-ext-cull-iter actions.")
	local extList = BuildCulledExtList(context)
	if(#extList > 0) then
		self:IterateChildren(context, extList, "extName")
	end
	return true --Stops regular child processing.
end

MakeActionType("core-ext-cull-iter", coreExtCullIterAction, function(self, data)
end)

conditionals["core-ext-cull-iter"] = function(context)
	assert(context.version, "Cannot have a core-ext-cull-iter conditional outside of a version.")
	return #BuildCulledExtList(context) > 0
end


----------------------------------------------
-- Enum Seen Action
local enumSeenAction = {}

function enumSeenAction:PreProcess(context)
	self:Assert(context.enumSeen == nil, "Cannot nest enum-seen actions.")
	context.enumSeen = {}
end

function enumSeenAction:PostProcess(context)
	context.enumSeen = nil
end

MakeActionType("enum-seen", enumSeenAction, function(self, data)
end)


-----------------------------------------------
-- Enumerator Iterator
local enumIterAction = {}

local function GetEnumList(context)
	if(context.extName) then
		--Get enum list for the extension.
		return context.specData.extdefs[context.extName].enums, context.extName
	else
		--Build list from core version.
		local core = context.specData.coredefs[context.version];
		
		if(context.options.profile ~= "core") then
			return core.enums
		end

		local targetVersion = tonumber(context.options.version)
		local enumList = {};
		for i, enum in ipairs(core.enums) do
			local bShouldWrite = true;
			
			if(enum.removed and tonumber(enum.removed) <= targetVersion) then
				bShouldWrite = false
			end

			--Very oddball logic to handle ARB_tessellation_shader's
			--ability to bring back GL_QUADS.
			--Remove the enumeration if all of the following
			--	The enum is from a core extension
			--	That extension is not core for the version we're writing
			if(enum.extensions) then
				for _, ext in ipairs(enum.extensions) do
					if(context.specData.coreexts[ext] and
						tonumber(context.specData.coreexts[ext].version) <= targetVersion) then
						bShouldWrite = false
					end
				end
			end

			if(bShouldWrite) then
				enumList[#enumList + 1] = enum;
			end
		end
		return enumList, context.version
	end
end

function enumIterAction:PreProcess(context)
	self:Assert(context.version or context.extName, "Enumeration iterators must go within a version or extension iterator.")

	local enumList, source = GetEnumList(context)

	context.enumTable = context.specData.enumtable
	self:IterateChildren(context, enumList, "enum",
		function(context, enum)
			if(context.enumSeen) then
				context.enumSeen[enum.name] = source
			end
		end)
	context.enumTable = nil
	return true --Stops regular child processing.
end

MakeActionType("enum-iter", enumIterAction, function(self, data)
end)

conditionals["enum-iter"] = function(context)
	assert(context.version or context.extName, "Cannot have an enum-iter conditional outside of a version or extension iterator.")

	return #GetEnumList(context) > 0
end

----------------------------------------------
-- Func Seen Action
local funcSeenAction = {}

function funcSeenAction:PreProcess(context)
	self:Assert(context.funcSeen == nil, "Cannot nest func-seen actions.")
	context.funcSeen = {}
end

function funcSeenAction:PostProcess(context)
	context.funcSeen = nil
end

MakeActionType("func-seen", funcSeenAction, function(self, data)
end)


-----------------------------------------------
-- Function Iterator
local funcIterAction = {}

local function GetFuncList(context)
	if(context.extName) then
		--Get function list for the extension.
		return context.specData.extdefs[context.extName].funcs, context.extName
	else
		--Build list from core version.
		local core = context.specData.coredefs[context.version];
		
		if(context.options.profile ~= "core") then
			return core.funcs
		end

		local targetVersion = tonumber(context.options.version)
		local funcList = {};
		for i, func in ipairs(core.funcs) do
			local bShouldWrite = true;
			
			if(func.deprecated and tonumber(func.deprecated) <= targetVersion) then
				bShouldWrite = false
			end

			--Fortuantely, a function can't be both from a version and an extension
			if(func.category and not string.match(func.category, "^VERSION")) then
				bShouldWrite = false
			end

			if(bShouldWrite) then
				funcList[#funcList + 1] = func;
			end
		end
		return funcList, context.version
	end
end

function funcIterAction:PreProcess(context)
	self:Assert(context.version or context.extName, "Function iterators must go within a version or extension iterator.")

	local funcList, source = GetFuncList(context)

	context.typemap = context.specData.typemap
	self:IterateChildren(context, funcList, "func",
		function(context, func)
			if(context.funcSeen) then
				context.funcSeen[func.name] = source
			end
		end)
	context.typemap = nil
	return true --Stops regular child processing.
end

MakeActionType("func-iter", funcIterAction, function(self, data)
end)

conditionals["func-iter"] = function(context)
	assert(context.version or context.extName, "Cannot have a func-iter conditional outside of a version or extension iterator.")

	return #GetFuncList(context) > 0
end

conditionals["core-funcs"] = function(context)
	return context.options.spec == "gl"
end



local struct = {}

function struct.BuildStructure(structure)
	local actions = {}
	for _, data in ipairs(structure) do
		actions[#actions + 1] = actionTypes[data.type](data)
	end
	
	actions.Proc = function(basename, style, specData, spec, options)
		local context = {}
		context.basename = basename
		context.style = style
		context.specData = specData
		context.spec = spec
		context.options = options
		
		context._coreExts = spec.GetCoreExts()
		context._extTbl = util.InvertTable(options.extensions)
		context._styles = { style }
		
		function context:GetStyle()
			return context._styles[#context._styles]
		end
		
		function context:FindStyleForFunc(funcName)
			for i = #context._styles, 1, -1 do
				if(context._styles[i][funcName]) then
					return context._styles[i]
				end
			end
			
			return nil
		end
		
		function context:PushStyle(newStyleName)
			assert(context._styles[1][newStyleName], "There is no style named " .. newStyleName)
			table.insert(context._styles, context._styles[1][newStyleName])
			context.style = context._styles[#context._styles]
		end
		
		function context:PopStyle()
			local ret = context._styles[#context._styles]
			context._styles[#context._styles] = nil
			context.style = context._styles[#context._styles]
			return ret
		end
		
		for _, action in ipairs(actions) do
			action:Process(context)
		end
	end
	
	return actions
end

return struct

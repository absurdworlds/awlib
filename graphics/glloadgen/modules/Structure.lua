
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
- file_style	Provided by file blocks. A file-specific subsection of `style`.
- extName		Provided by extension iterators.
- version		Provided by version iterators.
- enum			Provided by enum iterators.
- enumTable		Provided by enum iterators.
- enumSeen		Provided by enum seen blocks.
- func			Provided by function iterators.
- typemap		Provided by function iterators.
- funcSeen		Provided by func seen blocks.
]]

local actionTypes =
{
}

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

function action:CallFunction(style, context, name)
	name = name or self.name
	self:Assert(name, "Unknown function name.")
	self:Assert(style[name], "The style does not have a function " .. name)
	
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
	if(data.params) then
		local paramList = {}
		for param in data.params:gmatch("([_%a][_%w]*)") do
			paramList[#paramList + 1] = param
		end
		act.params = paramList
	end
	
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
	assert(context.style[self.file_style],
		"The style does not have a sub-section named " .. self.file_style)
	assert(context.hFile == nil, "You cannot nest `file` blocks.")

	context.file_style = context.style[self.file_style]
	local filename = self:CallFunction(context.file_style, context)
	
	local hFile = io.open(filename, "w")
	context.hFile = TabbedFile.TabbedFile(hFile, context.options.indent)
end

function fileAction:PostProcess(context)
	context.hFile:close()
	context.hFile = nil
	context.file_style = nil
end

MakeActionType("file", fileAction, function(self, data)
	assert(data.style, "File actions must have a `style`")

	self.file_style = data.style
	self.name = "GetFilename"
	self.params = self.params or {"basename", "options"}
end)


-------------------------------------
-- Block Action
local blockAction = {}

function blockAction:PreProcess(context)
	assert(context.file_style, "Cannot write a block outside of a file.")
	self:CallFunction(context.file_style, context, "WriteBlockBegin" .. self.name)
end

function blockAction:PostProcess(context)
	self:CallFunction(context.file_style, context, "WriteBlockEnd" .. self.name)
end

MakeActionType("block", blockAction, function(self, data)
	assert(data.name, "Block actions must have a `name`")

	self.name = data.name
	self.params = self.params or {"hFile", "spec", "options"}
end)


------------------------------------------
-- Write Action
local writeAction = {}

function writeAction:PreProcess(context)
	assert(context.file_style, "Cannot write data outside of a file.")
	self:CallFunction(context.file_style, context)
end

function writeAction:PostProcess(context)
end

MakeActionType("write", writeAction, function(self, data)
	assert(data.name, "Write actions must have a `name`")
	self.name = "Write" .. data.name
	self.params = self.params or {"hFile", "specData", "spec", "options"}
end)


------------------------------------------
-- Blank Action
local blankAction = {}

function blankAction:PreProcess(context)
	self:Assert(context.hFile, "Spaces must be in files.")
	context.hFile:write("\n")
end

MakeActionType("blank", blankAction, function(self, data)
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


---------------------------------------------
-- Core Extension Iterator Action
local coreExtIterAction = {}

function coreExtIterAction:PreProcess(context)
	self:Assert(context.version, "Must put this in a version iterator")
	self:Assert(context.extName == nil, "Cannot nest core-ext-iter actions.")
	local coreExts = context.spec.GetCoreExts()
	if(coreExts[context.version]) then
		self:IterateChildren(context, coreExts[context.version], "extName")
	end
	return true --Stops regular child processing.
end

MakeActionType("core-ext-iter", coreExtIterAction, function(self, data)
end)


---------------------------------------------
-- Core Extension Iterator Action, culled against the requested extensions.
local coreExtCullIterAction = {}

function coreExtCullIterAction:PreProcess(context)
	self:Assert(context.version, "Must put this in a version iterator")
	self:Assert(context.extName == nil, "Cannot nest core-ext-iter actions.")
	local coreExts = context.spec.GetCoreExts()
	if(coreExts[context.version]) then
		local extList = {}
		for _, ext in ipairs(coreExts[context.version]) do
			if(not context._extTbl[ext]) then
				extList[#extList + 1] = ext
			end
		end

		if(#extList > 0) then
			self:IterateChildren(context, extList, "extName")
		end
	end
	return true --Stops regular child processing.
end

MakeActionType("core-ext-cull-iter", coreExtCullIterAction, function(self, data)
end)


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
		
		for _, action in ipairs(actions) do
			action:Process(context)
		end
	end
	
	return actions
end

return struct

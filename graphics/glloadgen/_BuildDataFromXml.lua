

local function FindElementByName(xmlData, name)
	for _, node in ipairs(xmlData) do
		if(node._elem == name) then
			return node, xmlData
		end
		
		if(node._elem) then
			local testNode, parent = FindElementByName(node, name)
			if(testNode) then
				return testNode, parent
			end
		end
	end
	
	return nil, nil
end

local function BuildAllLists(xmlData, api)
	local allTypes = {}
	
	local typesNode = FindElementByName(xmlData, "types")
	assert(typesNode, "Could not find the `types` node.")
	for _, typeNode in ipairs(typesNode) do
		if(typeNode._elem == "type") then
			if(not typeNode.api or typeNode.api == api) then
				if(typeNode.name) then
					assert(allTypes[typeNode.name] == nil, "Multiply defined type " .. typeNode.name)
					allTypes[typeNode.name] = typeNode
				else
					--Get the node name.
					local nameElem = FindElementByName(typeNode, "name")
					assert(nameElem, "Type found with no name.")
					assert(type(nameElem[1]) == "string", "Name element of `type` is irregular.")
					assert(allTypes[nameElem[1]] == nil, "Multiply defined type " .. nameElem[1])
					allTypes[nameElem[1]] = typeNode
				end
			end
		end
	end
	
	local allFuncs = {}
	local commandsNode = FindElementByName(xmlData, "commands")
	for _, funcNode in ipairs(commandsNode) do
		if(funcNode._elem == "command") then
			local prototype = FindElementByName(funcNode, "proto")
			assert(prototype, "No `proto` node in a `command` node.")
			local funcNameNode = FindElementByName(prototype, "name")
			assert(funcNameNode, "No `name` node in the `proto` node of a `command`.")
			
			allFuncs[funcNameNode[1]] = funcNode
		end
	end
	
	local allEnums = {}
	for baseIx, node in ipairs(xmlData) do
		if(type(node) == "table" and node._elem == "enums") then
			for _, enumNode in ipairs(node) do
				if(type(enumNode) == "table" and enumNode._elem == "enum") then
					assert(enumNode.name, "An enum lacks a `name` attribute. " .. baseIx)
					
					if(not enumNode.api or enumNode.api == api) then
						assert(allEnums[enumNode.name] == nil, "The enum " .. enumNode.name .." was multiply defined.")
						allEnums[enumNode.name] = enumNode
					end
				end
			end
		end
	end
	
	return allTypes, allEnums, allFuncs
end

local function CollectFeatures(xmlData, feature_api)
	local features = {}
	
	for _, node in ipairs(xmlData) do
		if(type(node) == "table" and
			node._elem == "feature" and
			node.api == feature_api) then
			
			features[#features + 1] = node
		end
	end
	
	return features
end

local function TestSupport(support, test)
	for tester in support:gmatch("([^|]+)") do
		if(tester == test) then
			return true
		end
	end
	
	return false
end

local function CollectExtensions(xmlData, ext_support)
	local extensions = {}
	
	local extsNode = FindElementByName(xmlData, "extensions")
	assert(extsNode, "No `extensions` could be found.")
	
	for _, node in ipairs(extsNode) do
		if(type(node) == "table" and
			node._elem == "extension") then
			assert(node.name, "`extension` node has no name.")

			if(TestSupport(node.supported, ext_support)) then
				extensions[#extensions + 1] = node
			end
		end
	end

	return extensions
end

local function RemovePrefix(name, prefix)
	return name:match(prefix .. "(.+)")
end

local NewFeatureTbl = {}

function NewFeatureTbl.enum(enumMap, allEnums, name)
	local enumData = {}
	enumMap[name] = enumData
	
	assert(allEnums[name], "Could not find the enum " .. name)
	enumData.name = allEnums[name].name
	enumData.value = allEnums[name].value
	
	return enumData
end

local function TrimString(str)
	str = str:match("^%s*(.+)")
	str = str:match("(.+)%s+$") or str
	return str
end

function NewFeatureTbl.command(funcMap, allFuncs, name, typeRefs)
	local funcData = {}
	funcMap[name] = funcData
	
	assert(allFuncs[name], "Could not find the function " .. name)
	funcData.name = name

	local protoNode = FindElementByName(allFuncs[name], "proto")
	local returnType = ""
	for _, node in ipairs(protoNode) do
		if(type(node) == "string") then
			returnType = returnType .. node
		else
			if(node._elem == "ptype") then
				returnType = returnType .. node[1]
				typeRefs[node[1]] = true
			end
		end
	end
	
	funcData.return_ctype = TrimString(returnType)
	
	local params = {}
	funcData.parameters = params
	
	for _, node in ipairs(allFuncs[name]) do
		if(type(node) == "table" and node._elem == "param") then
			local ctype = ""
			local param = {}
			table.insert(params, param)
			
			for _, pnode in ipairs(node) do
				if(type(pnode) == "string") then
					ctype = ctype .. pnode
				elseif(type(pnode) == "table") then
					if(pnode._elem == "ptype") then
						ctype = ctype .. pnode[1]
						typeRefs[pnode[1]] = true
					elseif(pnode._elem == "name") then
						param.name = pnode[1]
						break
					end
				end
			end

			param.ctype = TrimString(ctype)
		end
	end
	
	return funcData
end

function NewFeatureTbl.type(typeRefs, allTypes, name)
	typeRefs[name] = true
	return true
end


local function CreateNewFeature(featureType, map, allFeat, name, ...)
	return NewFeatureTbl[featureType](map, allFeat, name, ...)
end

local function ExtractFeaturesFromList(featureType, map, allFeat,
		listNode, parentNode, feature_api, ext_support, ...)
		
	if(type(listNode) == "table" and listNode._elem) then
		if(not listNode.api or listNode.api == feature_api) then
			for _, featNode in ipairs(listNode) do
				if(type(featNode) == "table" and featNode._elem == featureType) then
					local featData = map[featNode.name]
					if(not featData) then
						featData = CreateNewFeature(featureType, map,
							allFeat, featNode.name, ...)
					end
					
					if(type(featData) == "table") then
						if(parentNode._elem == "extension") then
							featData.extensions = featData.extensions or {}
							table.insert(featData.extensions, parentNode.name)
						elseif(parentNode._elem == "feature") then
							featData.core = featData.core or {}
							local profile = "core"
							if(parentNode.profile == "compatibility" or
								listNode._elem == "remove") then

								profile = "compatibility"
							end
							table.insert(featData.core, {parentNode.number, profile})
						end
					end
				end
			end
		end
	end
end

local function SortCore(core)
	if(core and #core > 1) then
		table.sort(core, function(lhs, rhs)
			return tonumber(lhs[1]) < tonumber(rhs[1])
		end)
	end
end

local function CollateEnumerators(enums, allEnums, features, extensions,
	feature_api, ext_support)
	
	local enumMap = {}
	
	for _, version in ipairs(features) do
		for _, base in ipairs(version) do
			ExtractFeaturesFromList("enum", enumMap, allEnums, base, version,
				feature_api, ext_support)
		end
	end
	
	for _, ext in ipairs(extensions) do
		for _, base in ipairs(ext) do
			ExtractFeaturesFromList("enum", enumMap, allEnums, base, ext,
				feature_api, ext_support)
		end
	end

	for enumName, enumData in pairs(enumMap) do
		enums[#enums + 1] = enumData
		SortCore(enumData.core)
	end
end

local function CollateFunctions(funcs, allFuncs, features, extensions,
	feature_api, ext_support)
	
	local funcMap = {}
	local typeRefs = {}
	
	for _, version in ipairs(features) do
		for _, base in ipairs(version) do
			ExtractFeaturesFromList("command", funcMap, allFuncs, base, version,
				feature_api, ext_support, typeRefs)
		end
	end
	
	for _, ext in ipairs(extensions) do
		for _, base in ipairs(ext) do
			ExtractFeaturesFromList("command", funcMap, allFuncs, base, ext,
				feature_api, ext_support, typeRefs)
		end
	end

	for _, funcData in pairs(funcMap) do
		funcs[#funcs + 1] = funcData
		SortCore(funcData.core)
	end
	
	return typeRefs
end

local function CollateTypes(typeRefs, allTypes, features, extensions,
	feature_api, ext_support)
	
	for _, version in ipairs(features) do
		for _, base in ipairs(version) do
			ExtractFeaturesFromList("type", typeRefs, allTypes, base, version,
				feature_api, ext_support)
		end
	end
	
	for _, ext in ipairs(extensions) do
		for _, base in ipairs(ext) do
			ExtractFeaturesFromList("type", typeRefs, allTypes, base, ext,
				feature_api, ext_support)
		end
	end
end

local function BuildPassthruData(typeRefs, allTypes)
	local passthru = {}
	
	local typeHierarchy = {{}}
	local types = typeHierarchy[1]
	
	for typeName, _ in pairs(typeRefs) do
		table.insert(types, 1, typeName)
	end
	
	repeat
		local reqTypes = {}
		local lastTypes = typeHierarchy[#typeHierarchy]
		
		for _, typeName in ipairs(lastTypes) do
			if(allTypes[typeName].requires) then
				reqTypes[#reqTypes + 1] = allTypes[typeName].requires
			end
		end
		
		typeHierarchy[#typeHierarchy + 1] = reqTypes
	until (#reqTypes == 0)
	
	local inList = {}
	
	for i = #typeHierarchy, 1, -1 do
		local reqTypes = typeHierarchy[i]
		for _, typeName in ipairs(reqTypes) do
			if(not inList[typeName]) then
				inList[typeName] = true
				local str = ""
				for _, node in ipairs(allTypes[typeName]) do
					if(type(node) == "string") then
						str = str .. node
					else
						if(node._elem == "apientry") then
							str = str .. "APIENTRY"
						else
							str = str .. node[1]
						end
					end
				end
				
				if(#str > 0) then
					passthru[#passthru + 1] = str
				end
			end
		end
	end
	
	return passthru
end


local Build = {}

function Build.BuildData(xmlData, feature_api, ext_support, enum_prefix, func_prefix)
	local allTypes, allEnums, allFuncs = BuildAllLists(xmlData, feature_api)

	--Collate all of the relevant data.
	local features = CollectFeatures(xmlData, feature_api)
	local extensions = CollectExtensions(xmlData, ext_support)

	local ret = {}
	--Write each extension's name into the `extensions` array of the output.
	--Extracting the prefix.
	ret.extensions = {}
	for _, ext in ipairs(extensions) do
		table.insert(ret.extensions, RemovePrefix(ext.name, enum_prefix))
	end
	
	--Write the available version numbers.
	if(#features ~= 0) then
		ret.versions = {}
		for _, version in ipairs(features) do
			table.insert(ret.versions, version.number)
		end
	end
	
	--Extract the applicable enumerators.
	ret.enumerators = {}
	CollateEnumerators(ret.enumerators, allEnums, features,
		extensions, feature_api, ext_support)
	for _, enum in ipairs(ret.enumerators) do
		enum.name = RemovePrefix(enum.name, enum_prefix)
		if(enum.extensions) then
			for ix, extName in ipairs(enum.extensions) do
				enum.extensions[ix] = RemovePrefix(extName, enum_prefix)
			end
		end
	end

	--Extract the applicable functions.
	ret.funcData = {}
	ret.funcData.functions = {}
	local typeRefs = CollateFunctions(ret.funcData.functions, allFuncs, features,
		extensions, feature_api, ext_support)
	for _, func in ipairs(ret.funcData.functions) do
		func.name = RemovePrefix(func.name, func_prefix)
		if(func.extensions) then
			for ix, extName in ipairs(func.extensions) do
				func.extensions[ix] = RemovePrefix(extName, enum_prefix)
			end
		end
	end
	
	CollateTypes(typeRefs, allTypes, features, extensions,
		feature_api, ext_support)
	
	ret.funcData.passthru = BuildPassthruData(typeRefs, allTypes)

	return ret
end

return Build;

--[[Useful style utility functions. This file will contain commonly useful strings and functions that generate useful data.]]

local TabbedFile = require "TabbedFile"
local util = require "util"
local struct = require "Structure"

local common = {}

--Creates a tabbed file.
function common.CreateFile(filename, indent)
	local hFile = io.open(filename, "w")
	return TabbedFile.TabbedFile(hFile, indent)
end

--Retrieves the common typedefs used by OpenGL 1.1.
function common.GetStdTypedefs()
	return dofile(util.GetDataFilePath() .. "style_commontypedefs.lua")
end

--Writes passthru data from the specData, with proper indentation.
function common.WritePassthruData(hFile, strArray)
	for _, str in ipairs(strArray) do
		--unindent after #endif
		if(str:match("^#endif") or str:match("^#elif")) then
			hFile:dec()
		end
	
		hFile:write(str, "\n")
		
		--Indent after #if.
		if(str:match("^#if") or str:match("^#elif")) then
			hFile:inc()
		end
	end
end

function common.WriteExternCStart(hFile)
	hFile:write("#ifdef __cplusplus\n")
	hFile:write('extern "C" {\n')
	hFile:write("#endif //__cplusplus\n")
	hFile:write("\n")
end

function common.WriteExternCEnd(hFile)
	hFile:write("#ifdef __cplusplus\n")
	hFile:write('}\n')
	hFile:write("#endif //__cplusplus\n")
	hFile:write("\n")
end

--Determines the value of the enumeration.
local function ResolveEnumValue(enum, enumTable)
	if(enum.copy) then
		return common.ResolveEnumValue(enumTable[enum.value], enumTable),
			enum.value;
	else
		return enum.value;
	end
end
common.ResolveEnumValue = ResolveEnumValue

--Gets the return type for a function.
function common.GetFuncReturnType(func, typemap)
	return typemap[func["return"]] or func["return"]
end

local bIsKindPtr ={
	value = false,
	array = true,
	reference = true,
};

--Important due to name conflicts. Some names have to re-mapped to others.
--Won't really affect things.
local paramNameRemap = {
	near = "ren_near",
	far = "ren_far",
	array = "ren_array",
};

--Returns the parameter list as a string.
--Parameter list does not include parenthesis.
function common.GetFuncParamList(func, typemap, bWriteVarNames)
	local paramList = {}
	for i, param in ipairs(func.params) do
		local parameter = ""
		local paramType = typemap[param.type] or param.type;
		local paramName = "";
		if(bWriteVarNames) then paramName = param.name end
		if(paramNameRemap[paramName]) then paramName = paramNameRemap[paramName] end
		
		if(bIsKindPtr[param.kind]) then
			if(param.input) then
				--Input arrays are ALWAYS const.
				parameter = parameter .. "const ";
			end
			parameter = parameter .. string.format("%s *%s",
				paramType, paramName);
		else
			parameter = parameter .. string.format("%s %s",
				paramType, paramName);
		end
		paramList[#paramList + 1] = parameter
	end
	
	return table.concat(paramList, ", ");
end

--Retrieves the name of the function according to OpenGL.
function common.GetOpenGLFuncName(func, spec)
	return spec.FuncNamePrefix() .. func.name
end

function common.GetProcAddressName(spec)
	return "IntGetProcAddress"
end


--You give it a function that takes a const char*.
function common.GetProcessExtsFromStringFunc(funcFormat, arguments)
	return [[
static void ProcExtsFromExtString(const char *strExtList]] .. (arguments or "") .. [[)
{
	size_t iExtListLen = strlen(strExtList);
	const char *strExtListEnd = strExtList + iExtListLen;
	const char *strCurrPos = strExtList;
	char strWorkBuff[256];

	while(*strCurrPos)
	{
		//Get the extension at our position.
		int iStrLen = 0;
		const char *strEndStr = strchr(strCurrPos, ' ');
		int iStop = 0;
		if(strEndStr == NULL)
		{
			strEndStr = strExtListEnd;
			iStop = 1;
		}

		iStrLen = (int)((ptrdiff_t)strEndStr - (ptrdiff_t)strCurrPos);

		if(iStrLen > 255)
			return;

		strncpy(strWorkBuff, strCurrPos, iStrLen);
		strWorkBuff[iStrLen] = '\0';

		]] .. funcFormat:format("strWorkBuff") ..[[;

		strCurrPos = strEndStr + 1;
		if(iStop) break;
	}
}
]]
end

function common.GetParseVersionFromString()
	return [[
static void ParseVersionFromString(int *pOutMajor, int *pOutMinor, const char *strVersion)
{
	const char *strDotPos = NULL;
	int iLength = 0;
	char strWorkBuff[10];
	*pOutMinor = 0;
	*pOutMajor = 0;

	strDotPos = strchr(strVersion, '.');
	if(!strDotPos)
		return;

	iLength = (int)((ptrdiff_t)strDotPos - (ptrdiff_t)strVersion);
	strncpy(strWorkBuff, strVersion, iLength);
	strWorkBuff[iLength] = '\0';

	*pOutMajor = atoi(strWorkBuff);
	strDotPos = strchr(strVersion + iLength + 1, ' ');
	if(!strDotPos)
	{
		//No extra data. Take the whole rest of the string.
		strcpy(strWorkBuff, strVersion + iLength + 1);
	}
	else
	{
		//Copy only up until the space.
		int iLengthMinor = (int)((ptrdiff_t)strDotPos - (ptrdiff_t)strVersion);
		iLengthMinor = iLengthMinor - (iLength + 1);
		strncpy(strWorkBuff, strVersion + iLength + 1, iLengthMinor);
		strWorkBuff[iLengthMinor] = '\0';
	}

	*pOutMinor = atoi(strWorkBuff);
}
]]
end

local function DeepCopyTable(tbl)
	local ret = {}
	for key, value in pairs(tbl) do
		if(type(value) == "table") then
			ret[key] = DeepCopyTable(value)
		else
			ret[key] = value
		end
	end
	return ret
end

common.DeepCopyTable = DeepCopyTable

local my_struct =
{
	{ type="file", style="header", name="GetFilename",
		{ type="block", name="IncludeGuard(hFile, spec, options)",
			{ type="blank"},
			{ type="write", name="Init(hFile, spec, options)", },
			{ type="blank"},
			{ type="write", name="StdTypedefs(hFile, specData, options)",},
			{ type="blank"},
			{ type="write", name="SpecTypedefs(hFile, specData, options)",},
			{ type="blank"},
			{ type="block", name="Decl(hFile, spec, options)",
				{ type="block", name="ExtVarDecl(hFile, spec, options)", cond="ext-iter",
					{ type="ext-iter",
						{ type="write", name="ExtVariableDecl(hFile, extName, specData, spec, options)" },
						{ type="blank", last=true },
					},
				},
				{ type="block", name="EnumDecl(hFile, spec, options)",
					{ type="enum-seen",
						{ type="ext-iter",
							{type="enum-iter",
								{ type="write", name="EnumDecl(hFile, enum, enumTable, spec, options, enumSeen)", },
								{ type="blank", last=true },
							},
						},
						{ type="version-iter",
							{ type="core-ext-cull-iter",
								{type="enum-iter",
									{ type="write", name="EnumDecl(hFile, enum, enumTable, spec, options, enumSeen)", },
									{ type="blank", last=true },
								},
							},
							{type="enum-iter",
								{ type="write", name="EnumDecl(hFile, enum, enumTable, spec, options, enumSeen)", },
								{ type="blank", last=true },
							},
						},
					},
				},
				{ type="block", name="FuncDecl(hFile, spec, options)",
					{ type="func-seen",
						{ type="ext-iter",
							{ type="block", name="ExtFuncDecl(hFile, extName, spec, options)", cond="func-iter",
								{type="func-iter",
									{ type="write", name="FuncDecl(hFile, func, typemap, spec, options, funcSeen)", },
								},
							},
							{ type="blank"},
						},
						{ type="version-iter",
							{ type="core-ext-cull-iter",
								{ type="block", name="ExtFuncDecl(hFile, extName, spec, options)", cond="func-iter",
									{type="func-iter",
										{ type="write", name="FuncDecl(hFile, func, typemap, spec, options, funcSeen)", },
									},
								},
								{ type="blank"},
							},
							{type="func-iter",
								{ type="write", name="FuncDecl(hFile, func, typemap, spec, options, funcSeen)", },
								{ type="blank", last=true },
							},
						},
					},
				},
				{ type="block", name="SysDecl(hFile, spec, options)",
					{ type="write", name="UtilityDecls(hFile, spec, options)",},
					{ type="blank" },
					{ type="write", name="MainLoaderFuncDecl(hFile, spec, options)",},
					{ type="blank" },
					{ type="write", name="VersioningFuncDecls(hFile, spec, options)",},
					{ type="blank" },
				},
			},
		},
	},
	{ type="file", style="source", name="GetFilename",
		{ type="write", name="Includes(hFile, basename, spec, options)",},
		{ type="blank"},
		{ type="write", name="LoaderData(hFile, spec, options)",},
		{ type="blank"},
		{ type="block", name="Def(hFile, spec, options)",
			{ type="block", name="ExtVarDef(hFile, spec, options)",
				{ type="ext-iter",
					{ type="write", name="ExtVariableDef(hFile, extName, specData, spec, options)",},
					{ type="blank", last=true},
				},
			},
			{ type="func-seen",
				{ type="ext-iter",
					{ type="block", name="ExtFuncDef(hFile, extName, spec, options)", cond="func-iter",
						{ type="func-iter",
							{ type="write", name="FuncDef(hFile, func, typemap, spec, options, funcSeen)", },
						},
						{ type="blank"},
						{ type="block", name="ExtLoader(hFile, extName, spec, options)",
							{ type="func-iter",
								{ type="write", name="ExtFuncLoader(hFile, func, typemap, spec, options)", }
							}
						},
						{ type="blank"},
					},
				},
				{ type="block", name="CoreFuncDef(hFile, spec, options)",
					cond="core-funcs",
					{ type="version-iter",
						{ type="core-ext-cull-iter",
							{ type="block", name="ExtFuncDef(hFile, extName, spec, options)", cond="func-iter",
								{type="func-iter",
									{ type="write", name="FuncDef(hFile, func, typemap, spec, options, funcSeen)", },
								},
							},
							{ type="blank"},
						},
						{type="func-iter",
							{ type="write", name="FuncDef(hFile, func, typemap, spec, options, funcSeen)", },
							{ type="blank", last=true },
						},
					},
					{ type="block", name="CoreLoader(hFile, spec, options)",
						{ type="version-iter",
							{ type="core-ext-iter",
								{type="func-iter",
									{ type="write", name="CoreFuncLoader(hFile, func, typemap, spec, options)", },
								},
							},
							{type="func-iter",
								{ type="write", name="CoreFuncLoader(hFile, func, typemap, spec, options)", },
							},
						},
					},
					{ type="blank"},
				},
				{ type="write", name="ExtStringFuncDef(hFile, specData, spec, options, funcSeen)"},
			},
			{ type="block", name="SysDef(hFile, spec, options)",
				{ type="write", name="UtilityDefs(hFile, specData, spec, options)",},
				{ type="blank" },
				{ type="write", name="MainLoaderFunc(hFile, specData, spec, options)",},
				{ type="blank" },
				{ type="write", name="VersioningFuncs(hFile, specData, spec, options)",},
				{ type="blank" },
			},
		},
	},
}


my_struct = struct.BuildStructure(my_struct)

function common.GetStandardStructure()
	return my_struct
end

return common

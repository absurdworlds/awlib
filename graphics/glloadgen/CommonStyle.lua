--[[Useful style utility functions. This file will contain commonly useful strings and functions that generate useful data.]]

local TabbedFile = require "_TabbedFile"
local util = require "util"

local common = {}

--Creates a tabbed file.
function common.CreateFile(filename, indent)
	local hFile = io.open(filename, "wt")
	return TabbedFile.TabbedFile(hFile, indent)
end

function common.GetStdTypedefs()
	return dofile(util.GetDataFilePath() .. "style_commontypedefs.lua")
end

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

local function ResolveEnumValue(enum, enumTable)
	if(enum.copy) then
		return common.ResolveEnumValue(enumTable[enum.value], enumTable),
			enum.value;
	else
		return enum.value;
	end
end
common.ResolveEnumValue = ResolveEnumValue

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

function common.GetGLVersionQueryFunc()
	return [[
static void GetGLVersion(int *pOutMajor, int *pOutMinor, const char *strVersion)
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

--You give it a function that takes a const char*.
function common.GetProcessExtsFromStringFunc(funcToCall)
	return [[
static void ProcExtsFromExtString(const char *strExtList)
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

		]] .. funcToCall ..[[(strWorkBuff);

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

return common

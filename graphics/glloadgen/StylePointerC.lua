
local common = require "CommonStyle"


local my_style = {}
my_style.header = {}
my_style.source = {}

function my_style.WriteLargeHeading(hFile, headingName)
	hFile:write("/*", string.rep("*", #headingName), "*/\n")
	hFile:write("/*", headingName, "*/\n")
end

function my_style.WriteSmallHeading(hFile, headingName)
	hFile:write("/*", headingName, "*/\n")
end

----------------------------------------------------------------
-- Header file construction

function my_style.header.CreateFile(basename, options)
	local filename = basename .. ".h"
	return common.CreateFile(filename, options.indent), filename
end

function my_style.header.MakeIncludeGuard(prefix, specIncl)
	local str = "POINTER_C_GENERATED_HEADER_" .. specIncl .. "_H"
	if(#prefix > 0) then
		return prefix:upper() .. "_" .. str
	end
	
	return str
end

function my_style.header.WriteStdTypedefs(hFile, specData, options)
	local defArray = common.GetStdTypedefs()
	
	--Use include-guards for the typedefs, since they're common among
	--headers in this style.
	
	hFile:write("#ifndef GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS\n")
	hFile:write("#define GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS\n")
	hFile:write("\n")
	hFile:inc()
	
	for _, def in ipairs(defArray) do
		hFile:write(def)
	end
	
	hFile:dec()
	hFile:write("\n")
	hFile:write("#endif /*GL_LOAD_GEN_BASIC_OPENGL_TYPEDEFS*/\n")
	hFile:write("\n")
end

function my_style.header.WriteSpecTypedefs(hFile, specData, options)
	hFile:push()
	common.WritePassthruData(hFile, specData.funcData.passthru)
	hFile:write("\n")
	hFile:pop()
end

function my_style.header.WriteBeginDecl(hFile, specData, options)
	common.WriteExternCStart(hFile)
end

local function GetExtVariableName(ext, spec, options)
	return options.prefix .. spec.DeclPrefix() .. "ext_" .. ext
end

function my_style.header.WriteExtVariableDecl(hFile, ext, specData, spec, options)
	hFile:write("extern int ", GetExtVariableName(ext, spec, options), ";\n");
end

function my_style.header.WriteBeginEnumDeclBlock(hFile, specData, options) end

function my_style.header.WriteEndEnumDeclBlock(hFile, specData, options) end

function my_style.header.WriteEnumDecl(hFile, enum, enumTable, spec, options)
	hFile:fmt("#define %s%s = %s\n",
		spec.EnumNamePrefix(),
		enum.name,
		common.ResolveEnumValue(enum, enumTable))
end

function my_style.header.WriteEnumPrevDecl(hFile, enum, enumTable, spec, options, extName)
	hFile:fmt("/*Copied %s%s From: %s*/\n",
		spec.EnumNamePrefix(),
		enum.name,
		extName)
end

function my_style.header.WriteBeginFuncDeclBlock(hFile, specData, options)
end

local function GetFuncPtrName(func, spec, options)
	return options.prefix .. "_ptrc_".. spec.FuncNamePrefix() .. func.name
end

local function GetFuncPtrDef(hFile, func, typemap, spec, options)
	return string.format("%s (%s *%s)(%s)",
		common.GetFuncReturnType(func, typemap),
		spec.GetCodegenPtrType(),
		GetFuncPtrName(func, spec, options),
		common.GetFuncParamList(func, typemap))
end

function my_style.header.WriteFuncDecl(hFile, func, typemap, spec, options)
	--Declare the function pointer.
	hFile:write("extern ",
		GetFuncPtrDef(hFile, func, typemap, spec, options),
		";\n")
	
	--#define it to the proper OpenGL name.
	hFile:fmt("#define %s %s\n",
		common.GetOpenGLFuncName(func, spec),
		GetFuncPtrName(func, spec, options))
end

function my_style.header.WriteEndFuncDeclBlock(hFile, specData, options)
end

function my_style.header.WriteBeginExtFuncDeclBlock(hFile, extName,
	spec, options)
	hFile:fmt("#ifndef %s\n", spec.ExtNamePrefix() .. extName)
	hFile:fmt("#define %s 1\n", spec.ExtNamePrefix() .. extName)
end

function my_style.header.WriteEndExtFuncDeclBlock(hFile, extName,
	spec, options)
	hFile:fmt("#endif /*%s*/ \n", spec.ExtNamePrefix() .. extName)
end

local function GetStatusCodeEnumName(spec, options)
	return string.format("%s%sLoadStatus", options.prefix, spec.DeclPrefix())
end

local function GetStatusCodeName(name, spec, options)
	return string.format("%s%s%s", options.prefix, spec.DeclPrefix(), name)
end

function my_style.header.WriteStatusCodeDecl(hFile, spec, options)
	hFile:fmt("enum %s\n", GetStatusCodeEnumName(spec, options))
	hFile:write("{\n")
	hFile:inc()
		hFile:write(GetStatusCodeName("LOAD_FAILED", spec, options), " = 0,\n")
		hFile:write(GetStatusCodeName("LOAD_SUCCEEDED", spec, options), " = 1,\n")
		hFile:write(GetStatusCodeName("LOAD_PARTIAL", spec, options), " = 2,\n")
	hFile:dec()
	hFile:write("};\n")
end

local function DecorateFuncName(name, spec, options)
	return string.format("%s%s%s", options.prefix, spec.DeclPrefix(), name)
end

local function GetLoaderFuncName(spec, options)
	return DecorateFuncName("LoadFunctions", spec, options)
end

function my_style.header.WriteFuncLoaderDecl(hFile, spec, options)
	hFile:fmt("%s %s(%s);\n",
		GetStatusCodeEnumName(spec, options),
		GetLoaderFuncName(spec, options),
		spec.GetLoaderParams())
end

function my_style.header.WriteVersioningDecls(hFile, spec, options)
	--Only for GL
	if(options.spec ~= "gl") then
		return
	end
	
	hFile:fmt("int %s();\n", DecorateFuncName("GetMinorVersion", spec, options))
	hFile:fmt("int %s();\n", DecorateFuncName("GetMajorVersion", spec, options))
	hFile:fmt("int %s(int iMajorVersion, int iMinorVersion);\n",
		DecorateFuncName("IsVersionGEQ", spec, options))
end

function my_style.header.WriteEndDecl(hFile, specData, options)
	common.WriteExternCEnd(hFile)
end

--------------------------------------------------
-- Source file construction functions.

function my_style.source.CreateFile(basename, options)
	local filename = basename .. ".c"
	return common.CreateFile(filename, options.indent), filename
end

function my_style.source.WriteIncludes(hFile, spec, options)
	hFile:write("#include <stdlib.h>\n")
	hFile:write("#include <string.h>\n")
end

local function GetMapTableStructName(spec, options)
	return string.format("%s%sStrToExtMap", options.prefix, spec.DeclPrefix())
end

function my_style.source.WriteMapTableDefs(hFile, spec, options)
	hFile:write("typedef int (*PFN_LOADEXTENSION)()\n")
	hFile:fmt("typedef struct %s%sStrToExtMap_s\n",
		options.prefix, spec.DeclPrefix())
	hFile:write("{\n")
	hFile:inc()
	hFile:write("char *strExtensionName;\n")
	hFile:write("int *pExtensionVariable;\n")
	hFile:write("PFN_LOADEXTENSION LoadExtension;\n")
	hFile:dec()
	hFile:fmt("} %s\n", GetMapTableStructName(spec, options))
end

function my_style.source.WriteBeginDef(hFile, spec, options) end
function my_style.source.WriteEndDef(hFile, spec, options) end

function my_style.source.WriteExtVariableDef(hFile, ext, specData, spec, options)
	hFile:fmt("int %s = %s;\n", GetExtVariableName(ext, spec, options),
		GetStatusCodeName("LOAD_FAILED", spec, options));
end

function my_style.source.WriteBeginExtFuncDefBlock(hFile, extName, spec, options)
end

function my_style.source.WriteEndExtFuncDefBlock(hFile, extName, spec, options)
end

function my_style.source.WriteFuncDef(hFile, func, typemap, spec, options)
	--Declare the function pointer.
	hFile:fmt("%s = NULL;\n",
		GetFuncPtrDef(hFile, func, typemap, spec, options))
end

local function GetExtLoaderFuncName(extName, spec, options)
	return "Load_" .. extName;
end

function my_style.source.WriteBeginExtLoaderBlock(hFile, extName, spec, options)
	hFile:fmt("static int %s()\n", GetExtLoaderFuncName(extName, spec, options))
	hFile:write("{\n")
	hFile:inc()
	hFile:write("int numFailed = 0;\n")
end

function my_style.source.WriteEndExtLoaderBlock(hFile, extName, spec, options)
	hFile:write("return numFailed;\n")
	hFile:dec()
	hFile:write("}\n")
end

function my_style.source.WriteExtFuncLoader(hFile, func, typemap, spec, options)
	hFile:fmt('%s = %s("%s%s");\n',
		GetFuncPtrName(func, spec, options),
		common.GetProcAddressName(spec),
		spec.FuncNamePrefix(), func.name)
	hFile:fmt('if(!%s) numFailed++;\n', GetFuncPtrName(func, spec, options))
end

function my_style.source.WriteBeginCoreFuncDefBlock(hFile, version, spec, options)
end

function my_style.source.WriteEndCoreFuncDefBlock(hFile, version, spec, options)
end

local function GetCoreLoaderFuncName(version, spec, options)
	return "Load_Version_" .. version:gsub("%.", "_")
end

function my_style.source.WriteBeginCoreLoaderBlock(hFile, version, spec, options)
	hFile:fmt("static int %s()\n", GetCoreLoaderFuncName(version, spec, options))
	hFile:write("{\n")
	hFile:inc()
	hFile:write("int numFailed = 0;\n")
end

function my_style.source.WriteEndCoreLoaderBlock(hFile, version, spec, options)
	hFile:write("return numFailed;\n")
	hFile:dec()
	hFile:write("}\n")
end

function my_style.source.WriteCoreFuncLoader(hFile, func, typemap, spec, options)
	hFile:fmt('%s = %s("%s%s");\n',
		GetFuncPtrName(func, spec, options),
		common.GetProcAddressName(spec),
		spec.FuncNamePrefix(), func.name)

	--Special hack for DSA_EXT functions in core functions.
	--They do not count against the loaded count.
	if(func.name:match("EXT$")) then
		hFile:write("/*An EXT_direct_state_access-based function. Don't count it.*/")
	else
		hFile:fmt('if(!%s) numFailed++;\n', GetFuncPtrName(func, spec, options))
	end
end

function my_style.source.WriteUtilityDefs(hFile, specData, spec, options)
	hFile:write("Utilities\n")
end

--------------------------------------------------
-- Style retrieval machinery
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

local function Create()
	return DeepCopyTable(my_style)
end

return { Create = Create }

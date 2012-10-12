
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

local function GetExtVariableName(extName, spec, options)
	return options.prefix .. spec.DeclPrefix() .. "ext_" .. extName
end

function my_style.header.WriteExtVariableDecl(hFile, extName, specData, spec, options)
	hFile:write("extern int ", GetExtVariableName(extName, spec, options), ";\n");
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

function my_style.header.WriteMainLoaderFuncDecl(hFile, spec, options)
	hFile:fmt("%s %s(%s);\n",
		GetStatusCodeEnumName(spec, options),
		GetLoaderFuncName(spec, options),
		spec.GetLoaderParams())
end

function my_style.header.WriteVersioningFuncDecls(hFile, spec, options)
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

local function GetMapTableStructName(spec, options)
	return string.format("%s%sStrToExtMap", options.prefix, spec.DeclPrefix())
end

local function GetMapTableVarName()
	return "ExtensionMap"
end

function my_style.source.WriteUtilityDefs(hFile, specData, spec, options)
	--Write the struct for the mapping table.
	hFile:write("typedef int (*PFN_LOADEXTENSION)()\n")
	hFile:fmt("typedef struct %s%sStrToExtMap_s\n",
		options.prefix, spec.DeclPrefix())
	hFile:write("{\n")
	hFile:inc()
	hFile:write("char *extensionName;\n")
	hFile:write("int *extensionVariable;\n")
	hFile:write("PFN_LOADEXTENSION LoadExtension;\n")
	hFile:dec()
	hFile:fmt("} %s\n", GetMapTableStructName(spec, options))
	hFile:write "\n"
	
	--Write the mapping table itself.
	hFile:fmt("static %s %s[] = {\n",
		GetMapTableStructName(spec, options),
		GetMapTableVarName())
	hFile:inc()
	for _, extName in ipairs(options.extensions) do
		if(#specData.extdefs[extName].funcs > 0) then
			hFile:fmt('{"%s", &%s, %s},\n',
				spec.ExtNamePrefix() .. extName,
				GetExtVariableName(extName, spec, options),
				GetExtLoaderFuncName(extName, spec, options))
		else
			hFile:fmt('{"%s", &%s, NULL},\n',
				spec.ExtNamePrefix() .. extName,
				GetExtVariableName(extName, spec, options))
		end
	end
	hFile:dec()
	hFile:write("}\n")
	hFile:write "\n"
	
	hFile:fmt("static int g_extensionMapSize = %i;\n", #options.extensions);
	hFile:write "\n"
	
	--Write function to find map entry by name.
	hFile:fmt("static %s *FindExtEntry(const char *extensionName)\n",
		GetMapTableStructName(spec, options))
	hFile:write("{\n")
	hFile:inc()
	hFile:write("int loop;")
	hFile:fmt("%s *currLoc = %s",
		GetMapTableStructName(spec, options),
		GetMapTableVarName())
	hFile:writeblock([[
for(loop = 0; loop < g_extensionMapSize; ++loop, ++currLoc)
{
	if(strcasecmp(extensionName, currLoc->extensionName) == 0)
		return pCurrLoc;
}

return NULL;
]])
	hFile:dec()
	hFile:write("}\n")
	hFile:write "\n"

	--Write the function to clear the extension variables.
	hFile:fmt("static void ClearExtensionVars()\n")
	hFile:write("{\n")
	hFile:inc()
	for _, extName in ipairs(options.extensions) do
		hFile:fmt('%s = %s;\n',
			GetExtVariableName(extName, spec, options),
			GetStatusCodeName("LOAD_FAILED", spec, options))
	end
	hFile:dec()
	hFile:write("}\n")
	hFile:write "\n"
	
	--Write a function to get the version number from a string.
	if(options.version) then
		hFile:writeblock(common.GetGLVersionQueryFunc())
		hFile:write "\n"
	end

	--Write a function that loads an extension by name. It is called when
	--processing, so it should also set the extension variable based on the load.
	hFile:writeblock([[
static void LoadExtByName(const char *extensionName)
{
	]] .. GetMapTableStructName(spec, options) .. [[ *entry = NULL;
	entry = FindExtEntry(extensionName);
	if(entry)
	{
		if(entry->LoadExtension)
		{
			int numFailed = entry->LoadExtension();
			if(numFailed == 0)
			{
				*(entry->extensionVariable) = ]] ..
				GetStatusCodeName("LOAD_SUCCEEDED", spec, options) ..
				[[;
			}
			else
			{
				*(entry->extensionVariable) = ]] ..
				GetStatusCodeName("LOAD_PARTIAL", spec, options) ..
				[[ + numFailed;
			}
		}
		else
		{
			*(entry->extensionVariable) = ]] ..
			GetStatusCodeName("LOAD_SUCCEEDED", spec, options) ..
			[[;
		}
	}
}
]])

	hFile:write "\n"
	
end

function my_style.source.WriteMainLoaderFunc(hFile, specData, spec, options)
	--Write our ancillary extension function, per the spec/options

	--Write a function that walks the extension string and processes each one.
	hFile:writeblock(common.GetProcessExtsFromStringFunc("LoadExtByName"))
end

function my_style.source.WriteVersioningFuncs(hFile, specData, spec, options)
end

--[=[

[[
static void ProcExtsFromExtList()
{
	GLint iLoop;
	GLint iNumExtensions = 0;
	_ptrc_glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

	for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
	{
		const char *strExtensionName = (const char *)_ptrc_glGetStringi(GL_EXTENSIONS, iLoop);
		LoadExtByName(strExtensionName)
	}
}
]];

[[
int LoaderFunction()
{
	int numFailed = 0;
	ClearExtensionVars();
	
	{
		_ptrc_glGetString = IntGetProcAddress("glGetString");
		if(!_ptrc_glGetString) return ogl_LOAD_FAILED;	
		
		ProcExtFromExtString((const char *)_ptrc_glGetString(GL_EXTENSIONS));
	}
	else
	{
		_ptrc_glGetStringi = IntGetProcAddress("glGetStringi");
		if(!_ptrc_glGetStringi) return ogl_LOAD_FAILED;	
		_ptrc_glGetIntegerv = IntGetProcAddress("glGetIntegerv");
		if(!_ptrc_glGetIntegerv) return ogl_LOAD_FAILED;	
	}
	
	numFailed = Load_Version_3_3()
	
	if(numFailed == 0)
		return ogl_LOAD_SUCCEEDED;
	else
		return ogl_LOAD_PARTIAL + numFailed;
}
]];

]=]
--------------------------------------------------
-- Style retrieval machinery

local function Create()
	return common.DeepCopyTable(my_style)
end

return { Create = Create }

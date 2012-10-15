
local common = require "CommonStyle"

local my_style = {}
my_style.header = {}
my_style.source = {}

----------------------------------------------------
-- Global styling functions.
function my_style.WriteLargeHeading(hFile, headingName)
	hFile:write(string.rep("/", 6 + #headingName), "\n")
	hFile:write("// ", headingName, "\n")
	hFile:write(string.rep("/", 6 + #headingName), "\n")
end

function my_style.WriteSmallHeading(hFile, headingName)
	hFile:write("// ", headingName, "\n")
end

------------------------------------------------------
-- Header styling functions

function my_style.header.CreateFile(basename, options)
	local filename = basename .. ".hpp"
	return common.CreateFile(filename, options.indent), filename
end

local function GenIncludeGuardName(hFile, spec, options)
	local str = "POINTER_CPP_GENERATED_HEADER" ..
		spec.GetIncludeGuardString() .. "_HPP"

	if(#options.prefix > 0) then
		return options.prefix:upper() .. "_" .. str
	end
	
	return str
end

function my_style.header.WriteBeginIncludeGuard(hFile, spec, options)
	local inclGuard = GenIncludeGuardName(hFile, spec, options)
	
	hFile:fmt("#ifndef %s\n", inclGuard)
	hFile:fmt("#define %s\n", inclGuard)
end

function my_style.header.WriteEndIncludeGuard(hFile, spec, options)
	hFile:fmt("#endif //%s\n", GenIncludeGuardName(hFile, spec, options))
end

function my_style.header.WriteStdTypedefs(hFile, specData, spec, options)
	local defArray = common.GetStdTypedefs()
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
end

function my_style.header.WriteSpecTypedefs(hFile, specData, spec, options)
	hFile:push()
	common.WritePassthruData(hFile, specData.funcData.passthru)
	hFile:pop()
end

local function StartNamespace(hFile, namespaceName)
	hFile:fmt("namespace %s\n", namespaceName)
	hFile:write("{\n")
	hFile:inc()
end

local function EndNamespace(hFile, namespaceName)
	hFile:dec()
	hFile:fmt("} //namespace %s\n", namespaceName)
end

function my_style.header.WriteBeginDecl(hFile, spec, options)
	if(#options.prefix > 0) then
		StartNamespace(hFile, options.prefix)
	end
	StartNamespace(hFile, spec.FuncNamePrefix())
end

function my_style.header.WriteEndDecl(hFile, spec, options)
	EndNamespace(hFile, spec.FuncNamePrefix())
	if(#options.prefix > 0) then
		EndNamespace(hFile, options.prefix)
	end
end

local extBlockNamespace = "exts"
local extVariableTypeDefinition = [[
class LoadTest
{
private:
	//Safe bool idiom. Joy!
	typedef void (LoadTest::*bool_type)() const;
	void big_long_name_that_really_doesnt_matter() const {}
	
public:
	operator bool_type() const
	{
		return m_isLoaded ? &LoadTest::big_long_name_that_really_doesnt_matter : 0;
	}
	
	int GetNumMissing() const {return m_numMissing;}
	
	void IgnoreThis(bool isLoaded, int numMissing)
	{
		m_isLoaded = isLoaded;
		m_numMissing = numMissing;
	}
	
	LoadTest() : m_isLoaded(false), m_numMissing(0) {}
private:
	bool m_isLoaded;
	int m_numMissing;
};
]]

function my_style.header.WriteBeginExtVarDeclBlock(hFile, spec, options)
	StartNamespace(hFile, extBlockNamespace)
	hFile:writeblock(extVariableTypeDefinition)
	hFile:write("\n")
end

function my_style.header.WriteEndExtVarDeclBlock(hFile, spec, options)
	EndNamespace(hFile, extBlockNamespace)
end

local function GenExtensionVarName(extName, spec, options)
	return "var_" .. extName;
end

function my_style.header.WriteExtVariableDecl(hFile, extName,
	specData, spec, options)
	hFile:fmt("extern LoadTest %s;\n",
		GenExtensionVarName(extName, spec, options));
end

function my_style.header.WriteBeginEnumDeclBlock(hFile, spec, options)
	hFile:write("enum\n")
	hFile:write("{\n")
	hFile:inc()
end

function my_style.header.WriteEndEnumDeclBlock(hFile, spec, options)
	hFile:dec()
	hFile:write("}\n")
end

local function GenEnumName(enum)
	--Note: some enumerators start with characters C++ forbids as initial
	--identifiers. If we detect such an enum, prefix it with `_`.
	local enumName = enum.name
	if(not enumName:match("^[a-zA-Z_]")) then
		enumName = "_" .. enumName
	end
	
	return enumName
end

function my_style.header.WriteEnumDecl(hFile, enum, enumTable, spec, options)
	local enumName = GenEnumName(enum)
	local lenEnum = #enumName
	local numIndent = 33
	
	local numSpaces = numIndent - lenEnum
	if(numSpaces < 1) then
		numSpaces = 1
	end

	hFile:fmt("%s%s= %s,\n",
		enumName,
		string.rep(" ", numSpaces),
		common.ResolveEnumValue(enum, enumTable))
end

function my_style.header.WriteEnumPrevDecl(hFile, enum, enumTable, spec, options, extName)
	hFile:fmt("//%s taken from ext: %s\n", enum.name, extName)
end

function my_style.header.WriteBeginFuncDeclBlock(hFile, spec, options)
	--Block containing all spec function declarations.
end

function my_style.header.WriteEndFuncDeclBlock(hFile, spec, options)
	--Block containing all spec function declarations.
end

function my_style.header.WriteBeginExtFuncDeclBlock(hFile, extName, spec, options)
	--Block containing all spec function declarations for a particular extension.
	--Useful for include-guards around extension function pointers.
end

function my_style.header.WriteEndExtFuncDeclBlock(hFile, extName, spec, options)
	--Block containing all spec function declarations for a particular extension.
end

local function GenFuncPtrName(func, spec, options)
	return func.name
end

local function GenFuncPtrTypedefName(func, spec, options)
	return "PFN" .. GenFuncPtrName(func, spec, options):upper()
end

local function WriteFuncPtrTypedefStmt(hFile, func, typemap, spec, options)
	hFile:fmt("typedef %s (%s *%s)(%s);\n",
		common.GetFuncReturnType(func, typemap),
		spec.GetCodegenPtrType(),
		GenFuncPtrTypedefName(func, spec, options),
		common.GetFuncParamList(func, typemap))
end

local function GenFuncPtrDefDirect(func, typemap, spec, options)
	return string.format("%s (%s *%s)(%s)",
		common.GetFuncReturnType(func, typemap),
		spec.GetCodegenPtrType(),
		GenFuncPtrName(func, spec, options),
		common.GetFuncParamList(func, typemap))
end

local function GenFuncPtrDefTypedef(func, typemap, spec, options)
	return string.format("%s %s",
		GenFuncPtrTypedefName(func, spec, options),
		GenFuncPtrName(func, spec, options))
end

function my_style.header.WriteFuncDecl(hFile, func, typemap, spec, options)
	hFile:write("extern ",
		GenFuncPtrDefDirect(func, typemap, spec, options),
		";\n")
end

function my_style.header.WriteBeginSysDeclBlock(hFile, spec, options)
	StartNamespace(hFile, "sys")
end

function my_style.header.WriteEndSysDeclBlock(hFile, spec, options)
	EndNamespace(hFile, "sys")
end

function my_style.header.WriteUtilityDecls(hFile, spec, options)
	--Write declarations for public utility stuff. Enums for return values, etc.
end

function my_style.header.WriteMainLoaderFuncDecl(hFile, spec, options)
	hFile:write("LoadTest LoadFunctions(%s);\n", spec.GetLoaderParams())
end

function my_style.header.WriteVersioningFuncDecls(hFile, spec, options)
	hFile:writeblock([[
int GetMinorVersion();
int GetMajorVersion();
bool IsVersionGEQ(int majorVersion, int minorVersion);
]])
end

--------------------------------------------------
-- Source code styling functions.
function my_style.source.CreateFile(basename, options)
	return common.CreateFile(basename .. ".cpp", options.indent)
end

function my_style.source.WriteIncludes(hFile, spec, options)
	--Write the system include files for things you wish to use.
end

function my_style.source.WriteBeginDef(hFile, spec, options)
	--Block containing the entire set of definitions.
end

function my_style.source.WriteEndDef(hFile, spec, options)
	--Block containing the entire set of definitions.
end

function my_style.source.WriteBeginExtVarDefBlock(hFile, spec, options)
	--Block containing the extension variable definitions.
end

function my_style.source.WriteEndExtVarDefBlock(hFile, spec, options)
	--Block containing the extension variable definitions.
end

function my_style.source.WriteExtVariableDef(hFile, extName,
	specData, spec, options)
	--Writes the definition for the extension variable `extName`.
end

function my_style.source.WriteBeginExtFuncDefBlock(hFile, extName, spec, options)
	--Block containing the extension function definitions and load function
	--for the functions in the extension `extName`.
end

function my_style.source.WriteEndExtFuncDefBlock(hFile, extName, spec, options)
	--Block containing the extension function definitions and load function
	--for the functions in the extension `extName`.
end

function my_style.source.WriteFuncDef(hFile, func, typemap, spec, options)
	--Writes the definition of an extension function.
	--Function pointers should be declared with spec.GetCodegenPtrType().
	--common.GetFuncReturnType(func, typemap) and
	--common.GetFuncParamList(func, typemap) can get the function types.
	--A third parameter passed to GetFuncParamList can tell it to provide
	--parameter names.
	--common.GetOpenGLFuncName(func, spec) can be used to get the
	--proper OpenGL name of the function.
end

function my_style.source.WriteBeginExtLoaderBlock(hFile, extName, spec, options)
	--The start of the loader function for the extension `extName`.
	--The general idea is that this function should write the beginning of
	--a file-static function that will contain the results of later
	--WriteExtFuncLoader calls.
end

function my_style.source.WriteEndExtLoaderBlock(hFile, extName, spec, options)
	--The end of the loader function for the extension `extName`.
end

function my_style.source.WriteExtFuncLoader(hFile, func, typemap, spec, options)
	--Writes the code to load the function `func` into a function pointer.
	--It should also write test code to check if the pointer is null
	--and possibly deal with that in some way.
	--To get the name for the function that you should call to load a
	--pointer (which takes the string name of the function), use:
	--common.GetProcAddressName(spec)
end

function my_style.source.WriteBeginCoreFuncDefBlock(hFile, version, spec, options)
	--Block containing the core functions for `version`.
	--The block also contains the loading function for this version.
end

function my_style.source.WriteEndCoreFuncDefBlock(hFile, version, spec, options)
	--Block containing the core functions for `version`.
end

function my_style.source.WriteGetExtStringFuncDef(hFile, func, typemap,
	spec, options)
	--This should write a *file static* function definition for the
	--given function.
	--This is used to ensure that the function needed to get the extension
	--string will be available. Will only ever be called in WGL, because
	--wglGetExtensionStringARB is an extension function. In GL, glGetString
	--will always be there; even in post-3.0, glGetStringi is required to
	--be there. and glXQueryExtensionString is core GLX 1.4.
end

function my_style.source.WriteBeginCoreLoaderBlock(hFile, version, spec, options)
	--The start of the loader function for the version `version`.
	--The general idea is that this function should write the beginning of
	--a file-static function that will contain the results of later
	--WriteCoreFuncLoader calls.
end

function my_style.source.WriteEndCoreLoaderBlock(hFile, version, spec, options)
	--The end of the loader function for the version `version`.
end

function my_style.source.WriteCoreFuncLoader(hFile, func, typemap, spec, options)
	--Writes the code to load the function `func` into a function pointer.
	--It should also write test code to check if the pointer is null
	--and possibly deal with that in some way.
	--To get the name for the function that you should call to load a
	--pointer (which takes the string name of the function), use:
	--common.GetProcAddressName(spec)
	--This is separate from WriteExtFuncLoader because certain core extension
	--functions, like glTextureStorage2DEXT are from EXT_DSA, but not really.
	--So this is a way to not erronously report the absence of EXT_DSA
	--functions. If func.name ends in "EXT", then it's a DSA function,
	--so don't count it if it's not there.
end

function my_style.source.WriteBeginSysDefBlock(hFile, spec, options)
	--Block containing the definitions of the system functions.
	--IE: the functions (and other definitions) used by the user
	--to actually load things. Useful for wrapping it in a namespace.
end

function my_style.source.WriteEndSysDefBlock(hFile, spec, options)
	--Block containing the definitions of the system functions.
end

function my_style.source.WriteUtilityDefs(hFile, specData, spec, options)
	--Writes utility function definitions.
end

function my_style.source.WriteMainLoaderFunc(hFile, specData, spec, options)
	--Writes the actual loader function. Possibly also some utilities used
	--by it.
end

function my_style.source.WriteVersioningFuncs(hFile, specData, spec, options)
	--Write definitions for versioning functions.
	--Will only be called if using a spec that has a version (ie: OpenGL).
end


--------------------------------------------------
-- Style retrieval machinery

local function Create()
	return common.DeepCopyTable(my_style)
end

return { Create = Create }

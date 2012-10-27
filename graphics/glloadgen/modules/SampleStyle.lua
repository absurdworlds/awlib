
local common = require "CommonStyle"

local my_style = {}
my_style.header = {}
my_style.source = {}

----------------------------------------------------
-- Global styling functions.
function my_style.WriteLargeHeading(hFile, headingName)
	--Write a comment with headingName in it
	--It should be large and noticable.
end

function my_style.WriteSmallHeading(hFile, headingName)
	--Write a comment with headingName in it
	--It should ideally take only one line.
end

------------------------------------------------------
-- Header styling functions

function my_style.header.CreateFile(basename, options)
	--Append an extension to `basename` and use
	-- common.CreateFile(filename, options.indent)
	-- to create it. Don't forget to return BOTH the hFile and the filename,
	-- in that order.
--[[
	local filename = basename .. ".h"
	return common.CreateFile(filename, options.indent), filename
]]
end

local function GenIncludeGuardName(hFile, spec, options)
	--Attach spec.GetIncludeGuardString() to the include guard name.
	--Attach options.prefix to the include guard name too.
--[[
	local str = "REPLACE_WITH_STYLE_SPECIFIC_NAME" ..
		spec.GetIncludeGuardString() .. "_H"

	if(#options.prefix > 0) then
		return options.prefix:upper() .. "_" .. str
	end
	
	return str
]]
end

function my_style.header.WriteBeginIncludeGuard(hFile, spec, options)
	--Write an include-guard, if needed.
--[[
	local inclGuard = GenIncludeGuardName(hFile, spec, options)
	
	hFile:fmt("#ifndef %s\n", inclGuard)
	hFile:fmt("#define %s\n", inclGuard)
]]
end

function my_style.header.WriteEndIncludeGuard(hFile, spec, options)
	--End any written include-guard.
--[[
	hFile:fmt("#endif //%s\n", GenIncludeGuardName(hFile, spec, options))
]]
end

function my_style.header.WriteStdTypedefs(hFile, specData, spec, options)
	--Write the standard OpenGL typedefs. For C/C++, these come from
	--common.GetStdTypedefs()
	--You may want to use include-guards around the standard typedefs, as
	--they're used in many places and redefining them is bad.
--[[
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
	hFile:write("\n")
]]
end

function my_style.header.WriteSpecTypedefs(hFile, specData, spec, options)
	--The goal here is to write the pass-thru data.
	--This is best done with
	--common.WritePassthruData(hFile, specData.funcData.passthru)
end

function my_style.header.WriteBeginDecl(hFile, spec, options)
	--This block encompasses all definitions.
	--A good place for an `extern "C"` or namespace if needed
	--You can indent hFile.
end

function my_style.header.WriteEndDecl(hFile, spec, options)
	--This block encompasses all definitions.
end

function my_style.header.WriteBeginExtVarDeclBlock(hFile, spec, options)
	--This block encompasses all extension variable declarations.
	--A place for wrapping then in a namespace or whatever.
end

function my_style.header.WriteEndExtVarDeclBlock(hFile, spec, options)
	--This block encompasses all extension variable declarations.
end

function my_style.header.WriteExtVariableDecl(hFile, extName,
	specData, spec, options)
	--Write a variable declaration for extName. Use:
	--spec.DeclPrefix() to get a good spec prefix for these.
end

function my_style.header.WriteBeginEnumDeclBlock(hFile, spec, options)
	--Block containing every enumerator.
	--A good place for an `enum\n{\n` block.
	--You can indent hFile afterwards.
end

function my_style.header.WriteEndEnumDeclBlock(hFile, spec, options)
	--Block containing every enumerator.
end

function my_style.header.WriteEnumDecl(hFile, enum, enumTable, spec, options)
	--Writes an active enumerator from enum and enumTable.
	--common.ResolveEnumValue(enum, enumTable) can be used to
	--get the enumerator's value. Don't rely on enum.value.
	--Remember: the system needs to be defined such that name
	--conflicts can't happen with different prefixes. So a prefix has
	--to be used somewhere.
end

function my_style.header.WriteEnumPrevDecl(hFile, enum, enumTable, spec, options, extName)
	--Writes an inactive enumerator which was written into the extension extName.
	--You should write this as a comment if you can't have different enums
	--with the same value.
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

function my_style.header.WriteFuncDecl(hFile, func, typemap, spec, options)
	--Write a function declaration for `func`.
	--Function pointers should be declared with spec.GetCodegenPtrType().
	--common.GetFuncReturnType(func, typemap) and
	--common.GetFuncParamList(func, typemap) can get the function types.
	--A third parameter passed to GetFuncParamList can tell it to provide
	--parameter names.
	--common.GetOpenGLFuncName(func, spec) can be used to get the
	--proper OpenGL name of the function.
end

function my_style.header.WriteBeginSysDeclBlock(hFile, spec, options)
	--Block containing the declarations of the system functions.
	--IE: the functions (and other declarations) used to actually load things.
	--Useful for wrapping it in a namespace.
end

function my_style.header.WriteEndSysDeclBlock(hFile, spec, options)
	--Block containing the declarations of the system functions.
end

function my_style.header.WriteUtilityDecls(hFile, spec, options)
	--Write declarations for public utility stuff. Enums for return values, etc.
end

function my_style.header.WriteMainLoaderFuncDecl(hFile, spec, options)
	--Write declaration for the main loader function that loads extensions and
	--core stuff.
	--The parameters to this function are provided by
	--spec.GetLoaderParams().
end

function my_style.header.WriteVersioningFuncDecls(hFile, spec, options)
	--Write declarations for versioning functions.
	--Will only be called if using a spec that has a version (ie: OpenGL).
end

--------------------------------------------------
-- Source code styling functions.
function my_style.source.CreateFile(basename, options)
	--Create a source file. Use:
	--common.CreateFile(filename, options.indent)
	--To create it. You don't need to return the filename, just the hFile.
--[[
	return common.CreateFile(basename .. ".c", options.indent)
]]
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
	--The parameters to this function are provided by
	--spec.GetLoaderParams().
end

function my_style.source.WriteVersioningFuncs(hFile, specData, spec, options)
	--Write definitions for versioning functions.
	--Will only be called if using a spec that has a version (ie: OpenGL).
end


--------------------------------------------------
-- Style retrieval machinery

local function Create()
	return common.DeepCopyTable(my_style), common.GetStandardStructure()
end

return { Create = Create }

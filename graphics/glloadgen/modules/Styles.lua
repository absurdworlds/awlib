--[[This module is the interface to all of the style-based code generation facilities.

The module has a function called GetStyleList, which returns a list of all available styles.

This module has a function called GetStyle, which is given a style name. It will return a table of functions that can be evaluated to do different code generation tasks. This table contains:


- WriteLargeHeading(hFile, headingName)
--		Writes a comment heading to the file. A large one.

- WriteSmallHeading(hFile, headingName)
--		Writes a comment heading to the file. A small one.



- header.CreateFile(basename, options)
--		basename is the filename sans extension. It opens a TabbedFile from it, using the options in options. It returns two values: a TabbedFile, and the actual filename used.

- header.MakeIncludeGuard(prefix, specIncl)
--		specIncl is an include-guard string from the spec. It returns a string that includes the two strings, which is appropriate for use as an include-guard.

- header.WriteStdTypedefs(hFile, specData, spec, options)
--		Writes the standard typedefs.

- header.WriteSpecTypedefs(hFile, specData, spec, options)
--		Writes the typedefs from the spec. The "funcData.passthru" section.

- header.WriteBeginDecl(hFile, spec, options)
--		Writes any style-specific scoping stuff that begins the declaration section. This is useful for things like 'extern "C"' and so forth.
--	

- header.WriteEndDecl(hFile, spec, options)
--		Writes any style-specific scoping stuff that ends the declaration section. This is useful for things like 'extern "C"' and so forth.

- header.WriteExtVariableDecl(hFile, extName, specData, spec, options)
--		Writes the variable declaration for a single extension variable. These are the variables that are exposed so that the user can test to see if an extension loaded.

- header.WriteBeginEnumDeclBlock(hFile, spec, options)
--		Writes any style-specific scoping stuff that starts the enumerator block. This is for *all* enumerators. This is useful for wrapping all enumerators in an enum declaration.

- header.WriteEndEnumDeclBlock(hFile, spec, options)
--		Writes any style-specific scoping stuff that ends the enumerator block.

- header.WriteEnumDecl(hFile, enum, enumTable, spec, options)
--		Writes an enumerator.

- header.WriteEnumPrevDecl(hFile, enum, enumTable, spec, options, extName)
--		Writes an enumerator that was written previously. Should be written as a comment, as it could conflict. extName is the name of the extension where it was originally written.

- header.WriteBeginFuncDeclBlock(hFile, spec, options)
--	Write any style-specific scoping stuff that starts the function declaration block.

- header.WriteEndFuncDeclBlock(hFile, spec, options)
--	Write any style-specific scoping stuff that ends the function declaration block.

- header.WriteBeginExtFuncDeclBlock(hFile, extName, spec, options)
-- Used for starting the declarations for a partiuclar extension.

- header.WriteEndExtFuncDeclBlock(hFile, extName, spec, options)
-- Used for ending the declarations for a partiuclar extension.

- header.WriteFuncDecl(hFile, func, typemap, spec, options)
--	Writes a function declaration. This can include multiple statements, such as a typedef, an extern function pointer declaration, and a #define or whatever.

- header.WriteStatusCodeDecl(hFile, spec, options)
--	Writes any declarations for status codes as returned from the loader and so forth.

- header.WriteMainLoaderFuncDecl(hFile, spec, options)
--	Writes the declaration for the main loading function.

- header.WriteVersioningFuncDecls(hFile, spec, options)
--	Writes the declarations for any functions used to help the user get versioning info. Will only be called if the spec has versions.


- source.CreateFile(basename, options)
--		basename is the filename sans extension. It opens a TabbedFile from it, using the options in options. It returns two values: a TabbedFile, and the actual filename used.

- source.WriteIncludes(hFile, spec, options)
--	Writes the include files for standard library stuff.

- source.WriteBeginDef(hFile, spec, options)
--	Writes any scoping for the block of definitions.

- source.WriteEndDef(hFile, spec, options)
--	Ends any scoping for the block of definitions.

- source.WriteExtVariableDef(hFile, ext, specData, spec, options)
--	Writes the extension variable definition for `ext`.

- source.WriteBeginExtFuncDefBlock(hFile, extName, spec, options)
--	Writes the beginning of an extension's block that contains function pointer definitions and the loader function for this extension.

- source.WriteEndExtFuncDefBlock(hFile, extName, spec, options)
--	Writes the ending of an extension's block that contains function pointer definitions and the loader function for this extension.

- source.WriteFuncDef(hFile, func, typemap, spec, options)
--	Writes a function pointer definition for the given function.

- source.WriteBeginExtLoaderBlock(hFile, extName, spec, options)
--	Writes the beginning of an extension loader function.

- source.WriteEndExtLoaderBlock(hFile, extName, spec, options)
--	Writes the ending of an extension loader function.

- source.WriteExtFuncLoader(hFile, func, typemap, spec, options)
--	Writes the code that goes inside an extension loader function that loads and tests a single extension function pointer.

- source.WriteBeginCoreFuncDefBlock(hFile, version, spec, options)
--	Writes the beginning of the core loader's block that contains function pointer definitions and the loader function for `version`.

- source.WriteEndCoreFuncDefBlock(hFile, version, spec, options)
--	Writes the end of the core loader's block that contains function pointer definitions and the loader function for `version`.

- source.WriteGetExtStringFuncDef(hFile, func, typemap, spec, options)
--	Writes a function definition for the function that gets the extension string list. It is written outside of ALL block definitions, so if you need scoping, scope it internally. Will only be called if the function's definition was not previously written.

- source.WriteBeginCoreLoaderBlock(hFile, version, spec, options)
--	Writes the start of the actual function that loads the function pointers for `version`.

- source.WriteEndCoreLoaderBlock(hFile, version, spec, options)
--	Writes the end of the actual function that loads the function pointers for `version`.

- source.WriteCoreFuncLoader(hFile, func, typemap, spec, options)
--	Writes the code that goes inside the core loader function that loads and tests a single extension function pointer.

- source.WriteUtilityDefs(hFile, specData, spec, options)
--	A place for writing utilities that will be needed by the function loader code. This can be a mapping table for mapping from extension name to loader funcs and extension variables or whatever you need to do the loading.

- source.WriteMainLoaderFunc(hFile, specData, spec, options)
--	Writes the implementation of the main loader function.

- source.WriteVersioningFuncs(hFile, specData, spec, options)
--	Writes the implementation of any versioning functions.


If you want to extend this to new styles, then add a module for your style, import it, and register it's module table with the registry. Your module should export a function `Create` which takes no parameters and returns a table as defined above.
]]

local style_registry =
{
	pointer_c = require("StylePointerC"),
}

local default_style = "pointer_c"



local function GetStyleList()
	--Make sure the default is first.
	local list = {default_style}
	assert(style_registry[default_style], "Bad default style.")
	
	for style, data in pairs(style_registry) do
		if(style ~= default_style) then
			list[#list + 1] = style
		end
	end
	
	return list
end

local function GetStyle(name)
	assert(style_registry[name], "Unknown style named " .. name)
	
	return style_registry[name].Create()
end

return{
	GetStyleList = GetStyleList,
	GetStyle = GetStyle,
}

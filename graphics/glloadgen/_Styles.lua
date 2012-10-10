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

- header.WriteStdTypedefs(hFile, specData, options)
--		Writes the standard typedefs.

- header.WriteSpecTypedefs(hFile, specData, options)
--		Writes the typedefs from the spec. The "funcData.passthru" section.

- header.WriteBeginDecl(hFile, specData, options)
--		Writes any style-specific scoping stuff that begins the declaration section. This is useful for things like 'extern "C"' and so forth.
--	

- header.WriteEndDecl(hFile, specData, options)
--		Writes any style-specific scoping stuff that ends the declaration section. This is useful for things like 'extern "C"' and so forth.

- header.WriteExtVariableDecl(hFile, ext, specData, spec, options)
--		Writes the variable declaration for a single extension variable. These are the variables that are exposed so that the user can test to see if an extension loaded.

- header.WriteBeginEnumDeclBlock(hFile, specData, options)
--		Writes any style-specific scoping stuff that starts the enumerator block. This is for *all* enumerators. This is useful for wrapping all enumerators in an enum declaration.

- header.WriteEndEnumDeclBlock(hFile, specData, options)
--		Writes any style-specific scoping stuff that ends the enumerator block.

- header.WriteEnumDecl(hFile, enum, enumTable, spec, options)
--		Writes an enumerator.

- header.WriteEnumPrevDecl(hFile, enum, enumTable, spec, options, extName)
--		Writes an enumerator that was written previously. Should be written as a comment, as it could conflict. extName is the name of the extension where it was originally written.

- header.WriteBeginFuncDeclBlock(hFile, specData, options)
--	Write any style-specific scoping stuff that starts the function declaration block.

- header.WriteEndFuncDeclBlock(hFile, specData, options)
--	Write any style-specific scoping stuff that ends the function declaration block.

- header.WriteBeginExtFuncDeclBlock(hFile, extName, spec, options)
-- Used for starting the declarations for a partiuclar extension.

- header.WriteEndExtFuncDeclBlock(hFile, extName, spec, options)
-- Used for ending the declarations for a partiuclar extension.

- header.WriteFuncDecl(hFile, func, typemap, spec, options)
--	Writes a function declaration. This can include multiple statements, such as a typedef, an extern function pointer declaration, and a #define or whatever.

- header.WriteStatusCodeDecl(hFile, spec, options)
--	Writes any declarations for status codes as returned from the loader and so forth.

- header.WriteFuncLoaderDecl(hFile, spec, options)
--	Writes the declaration for the main loading function.

- header.WriteVersioningDecls(hFile, spec, options)
--	Writes the declarations for any functions used to help the user get versioning info. Will only be called if the spec has versions.


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

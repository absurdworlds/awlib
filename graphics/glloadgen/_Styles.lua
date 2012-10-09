--[[This module is the interface to all of the style-based code generation facilities.

The module has a function called GetStyleList, which returns a list of all available styles.

This module has a function called GetStyle, which is given a style name. It will return a table of functions that can be evaluated to do different code generation tasks. This table contains:

- header.CreateFile(basename, options)
--		basename is the filename sans extension. It opens a TabbedFile from it, using the options in options.

- header.MakeIncludeGuard(prefix, specIncl)
--		specIncl is an include-guard string from the spec. It returns a string that includes the two strings, which is appropriate for use as an include-guard.




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

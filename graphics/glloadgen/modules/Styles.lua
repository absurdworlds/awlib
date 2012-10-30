--[[This module is the interface to all of the style-based code generation facilities.

The module has a function called GetStyleList, which returns a list of all available styles.

This module has a function called GetStyle, which is given a style name. It will return a table of functions that can be evaluated to do different code generation tasks.

SampleStyle.lua contains an example, with documentation for what's going on. Every function you need to define will be there, with comments. Just copy and use as needed.

If you want to extend this to new styles, then add a module for your style, import it, and register it's module table with the style_registry. Your module should export a function `Create` which takes no parameters and returns a table as defined above.
]]

local style_registry =
{
	pointer_c = require("StylePointerC"),
	pointer_cpp = require("StylePointerCPP"),
	glload = require("StyleGLLoad"),
	noload_cpp = require("StyleNoloadCpp"),
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

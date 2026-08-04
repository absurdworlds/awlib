-- Lua 5.1 compatibility shims
unpack = unpack or table.unpack
loadstring = loadstring or load

local LoadXml = require "LoadXml"
require "_TableWriter"
local Build = require "_BuildDataFromXml"

local specs =
{
	{file="gl.xml", out="glspec.lua", api="gl",  support="gl",  enumPrefix="GL_",  funcPrefix="gl"},
	{file="wgl.xml", out="wglspec.lua", api=nil, support="wgl", enumPrefix="WGL_", funcPrefix="wgl"},
	{file="glx.xml", out="glxspec.lua", api=nil, support="glx", enumPrefix="GLX_", funcPrefix="glX"},
}

for _, spec in ipairs(specs) do
	local xmlData, errors = LoadXml.LoadXml("newglspecs/" .. spec.file)

	local data = Build.BuildData(xmlData, spec.api,
		spec.support, spec.enumPrefix, spec.funcPrefix)

	local hFile = io.open("newglspecs/" .. spec.out, "w")
	hFile:write("return ")
	WriteTable(hFile, data)
	hFile:write(";\n")
	hFile:close()
end


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

local function exists(path)
	local file = io.open(path, "r")
	if file then file:close() end
	return file ~= nil
end

for _, spec in ipairs(specs) do
	local xmlPath = "newglspecs/" .. spec.file

	if not exists(xmlPath) then
		io.stderr:write("skipping " .. spec.file .. ": not present\n")
	else
		local xmlData, errors = LoadXml.LoadXml(xmlPath)

		local data = Build.BuildData(xmlData, spec.api,
			spec.support, spec.enumPrefix, spec.funcPrefix)

		local hFile = io.open("newglspecs/" .. spec.out, "w")
		hFile:write("return ")
		WriteTable(hFile, data)
		hFile:write(";\n")
		hFile:close()

		io.stderr:write(spec.file .. " -> " .. spec.out .. "\n")
	end
end


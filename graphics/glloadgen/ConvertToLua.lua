--[[
Converts the Khronos registry XML into the Lua spec tables LoadGen reads.

	lua ConvertToLua.lua [xml-dir] [spec-dir]

Defaults are <script-dir>/xml and <script-dir>/glspecs.
]]

-- Lua 5.1 compatibility shims
unpack = unpack or table.unpack
loadstring = loadstring or load

local here = arg[0]:match("^(.*)[/\\][^/\\]*$") or "."
package.path = here .. "/?.lua;" .. here .. "/SLAXML/?.lua;" .. package.path

local xmlDir  = arg[1] or (here .. "/xml")
local specDir = arg[2] or (here .. "/glspecs")

local LoadXml = require "LoadXml"
require "TableWriter"
local Build = require "BuildDataFromXml"

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
	local xmlPath = xmlDir .. "/" .. spec.file

	if not exists(xmlPath) then
		io.stderr:write("skipping " .. spec.file .. ": not present\n")
	else
		local xmlData, errors = LoadXml.LoadXml(xmlPath)

		local data = Build.BuildData(xmlData, spec.api,
			spec.support, spec.enumPrefix, spec.funcPrefix)

		local hFile = io.open(specDir .. "/" .. spec.out, "w")
		hFile:write("return ")
		WriteTable(hFile, data)
		hFile:write(";\n")
		hFile:close()

		io.stderr:write(spec.file .. " -> " .. spec.out .. "\n")
	end
end


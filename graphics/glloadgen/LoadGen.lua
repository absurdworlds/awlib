assert(arg and arg[0], "You ran this script incorrectly.")

--Get the location of our modules relative to here.
local baseDir = arg[0]:match("^(.*[\\/])")
baseDir = baseDir or "./"
assert(baseDir, arg[0] .. " No directory")

--Fixup the package path to be relative to this directory.
package.path = baseDir .. "modules/?.lua;" .. package.path

--Make a function to get the correct directory name.
function SysRelPath(relativePath)
	return baseDir .. relativePath
end
FixupPath = SysRelPath --Older name.

local opts = require "GetOptions"
local gen = require "Generate"

local options = opts.GetOptions(arg)

--[[{
	"test",
	"-spec=gl",
	"-extfile=exts.txt",
	"-version=3.3",
	"-profile=core",
}]]

gen.Generate(options)


--[[
local writer = require "tablewriter"
writer.WriteTable(io.stdout, options)
]]

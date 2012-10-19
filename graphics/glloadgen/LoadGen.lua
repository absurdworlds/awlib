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

local status, options = pcall(opts.GetOptions, arg)

if(not status) then
	io.write(options, "\n")
	return
end

gen.Generate(options)



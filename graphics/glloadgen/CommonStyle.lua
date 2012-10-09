--[[Useful style utility functions. This file will contain commonly useful strings and such.

]]

local TabbedFile = require "_TabbedFile"

local common = {}

--Creates a tabbed file.
function common.CreateFile(filename, indent)
	local hFile = io.open(filename, "wt")
	return TabbedFile.TabbedFile(hFile, indent)
end

return common

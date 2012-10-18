
local util = {}

function util.GetSpecFilePath()
	return FixupPath("glspecs/");
end

function util.GetDataFilePath()
	return FixupPath("data/");
end

function util.InvertTable(tbl)
	local ret = {}
	for i, val in ipairs(tbl) do
		ret[val] = true
	end
	return ret
end

--Returns two values: the base filename and the directory.
--If the base filename is nil, it doesn't have a pathname.
--If the directory is nil, then there was no directory.
function util.ParsePath(pathname)
	local base = pathname:match("([^\\/]+)$")
	local dir = pathname:match("^(.*[\\/])")
	
	return base, dir
end

local function DeepCopyTable(tbl, destTbl)
	local ret = destTbl or {}
	for key, value in pairs(tbl) do
		if(type(value) == "table") then
			if(type(ret[key]) == "table") then
				ret[key] = DeepCopyTable(value, ret[key])
			else
				ret[key] = DeepCopyTable(value)
			end
		else
			ret[key] = value
		end
	end
	return ret
end

util.DeepCopyTable = DeepCopyTable

return util

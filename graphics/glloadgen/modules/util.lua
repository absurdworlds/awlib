
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

return util

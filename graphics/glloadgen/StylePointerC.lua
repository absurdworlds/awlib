
local common = require "CommonStyle"


local my_style = {}
my_style.header = {}
my_style.source = {}

function my_style.header.CreateFile(basename, options)
	return common.CreateFile(basename .. ".h", options.indent)
end

function my_style.header.MakeIncludeGuard(prefix, specIncl)
	local str = "POINTER_C_GENERATED_HEADER_" .. specIncl .. "_H"
	if(#prefix > 0) then
		return prefix:upper() .. "_" .. str
	end
	
	return str
end


--------------------------------------------------
-- Style retrieval machinery
local function DeepCopyTable(tbl)
	local ret = {}
	for key, value in pairs(tbl) do
		if(type(value) == "table") then
			ret[key] = DeepCopyTable(value)
		else
			ret[key] = value
		end
	end
	return ret
end

local function Create()
	return DeepCopyTable(my_style)
end

return { Create = Create }

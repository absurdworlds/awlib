
-- Project templates
dofile "sources/premake-setup.lua";

local modules = os.matchdirs("sources/hr*");

-- Process all modules
for i, dir in ipairs(modules)
	local filename = string.format("%s/premake.lua", dir);
	if(os.isfile(filename)) then
		dofile(filename);
	end
--	include(dir);
end

-- local examples = os.matchdirs("example/hrexample*");

-- Process all examples
--for i, dir in ipairs(modules)
--	local filename = string.format("%s/premake.lua", dir);
--	if(os.isfile(filename)) then
--		dofile(filename);
--	end
--end

-- Project templates
dofile "source/premake-setup.lua";

-- Create solution
SetupSolution();

local modules = os.matchdirs("source/hr*");

-- Process all modules
for i, dir in ipairs(modules) do
	local filename = string.format("%s/premake.lua", dir);
	if(os.isfile(filename)) then
		dofile(filename);
	end
--	include(dir);
end

-- Create solution
SetupSolution();

-- local examples = os.matchdirs("example/hrexample*");

-- Process all examples
--for i, dir in ipairs(modules)
--	local filename = string.format("%s/premake.lua", dir);
--	if(os.isfile(filename)) then
--		dofile(filename);
--	end
--end
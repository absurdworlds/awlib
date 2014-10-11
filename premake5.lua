
-- Project templates
dofile "source/premake5-setup.lua";

local modules = os.matchdirs("source/*");

-- Create solution
SetupSolution();

-- Process all modules
for i, dir in ipairs(modules) do
	local filename = string.format("%s/premake.lua", dir);
	if(os.isfile(filename)) then
		print ("Making " .. filename .. "...");
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
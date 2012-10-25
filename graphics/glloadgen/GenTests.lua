

local tests =
{
	[[lua $<dir>LoadGen.lua -spec=gl -version=3.3 -profile=core -style=pointer_cpp -stdext=extfiles/gl_ubiquitous.txt $<dir>test/ptr_cpp/test]],
}

local platTests =
{
	wgl =
	{
		[[lua $<dir>LoadGen.lua -spec=wgl -style=pointer_cpp -stdext=extfiles/wgl_common.txt $<dir>test/ptr_cpp/test]],
	},
	
	glX =
	{
	},
}

local glXTests = {}

local baseDir = arg[0]:match("^(.*[\\/])")
baseDir = baseDir or "./"

local function ExecTests(testList)
	for _, test in ipairs(testList) do
		test = test:gsub("%$<dir>", baseDir)
		print(test)
		os.execute(test)
	end
end

if(arg[1]) then
	assert(platTests[arg[1]], "Invalid platform " .. arg[1])
end

ExecTests(tests)
if(arg[1]) then
	ExecTests(platTests[arg[1]])
end


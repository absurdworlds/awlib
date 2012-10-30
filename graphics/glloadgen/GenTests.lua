
local prelims =
{
	[[lua $<dir>MakeAllExts.lua -spec=gl $<dir>allgl.txt]],
	[[lua $<dir>MakeAllExts.lua -spec=wgl $<dir>allwgl.txt]],
	[[lua $<dir>MakeAllExts.lua -spec=glX $<dir>allglx.txt]],
}

local tests =
{
	[[lua $<dir>LoadGen.lua -spec=gl -version=3.3 -profile=core -style=pointer_cpp -stdext=extfiles/gl_ubiquitous.txt $<dir>test/ptr_cpp/test]],
	[[lua $<dir>LoadGen.lua -spec=gl -version=4.3 -profile=compatibility -style=glload -extfile=$<dir>allgl.txt $<dir>test/glload_c/test]],
	[[lua $<dir>LoadGen.lua -spec=gl -version=4.3 -profile=compatibility -style=glload -extfile=$<dir>allgl.txt $<dir>test/glload_cpp/test]],
	[[lua $<dir>LoadGen.lua -spec=gl -version=3.3 -profile=compatibility -style=glee_cpp  -stdext=extfiles/gl_ubiquitous.txt $<dir>test/glee_cpp/test]],
}

local platTests =
{
	wgl =
	{
		[[lua $<dir>LoadGen.lua -spec=wgl -style=pointer_cpp -stdext=extfiles/wgl_common.txt $<dir>test/ptr_cpp/test]],
		[[lua $<dir>LoadGen.lua -spec=wgl -style=glload -extfile=$<dir>allwgl.txt $<dir>test/glload_c/test]],
		[[lua $<dir>LoadGen.lua -spec=wgl -style=glload -extfile=$<dir>allwgl.txt $<dir>test/glload_cpp/test]],
		[[lua $<dir>LoadGen.lua -spec=wgl -style=glee_cpp  -stdext=extfiles/wgl_common.txt $<dir>test/glee_cpp/test]],
	},
	
	glX =
	{
		[[lua $<dir>LoadGen.lua -spec=glX -style=pointer_cpp -stdext=extfiles/glx_common.txt $<dir>test/ptr_cpp/test]],
		[[lua $<dir>LoadGen.lua -spec=glX -style=glload -extfile=$<dir>allglx.txt $<dir>test/glload_c/test]],
		[[lua $<dir>LoadGen.lua -spec=glX -style=glload -extfile=$<dir>allglx.txt $<dir>test/glload_cpp/test]],
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

ExecTests(prelims)
ExecTests(tests)
if(arg[1]) then
	ExecTests(platTests[arg[1]])
end


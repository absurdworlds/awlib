--[[ The function GetOptions retrieves the list of extensions and other command-line options. It pulls data from a multitude of sources, though it begins with the command-line.

It takes the following parameters:
- An array of the command-line options.

It returns a table containing the following entries:
- spec: What specification will be generated. One of the following:
-		gl: Uses the OpenGL spec. Default
-		glX: Uses the glX spec.
-		wgl: Uses the WGL "spec".
- version: OpenGL version to export. All core features from that version and below will be exported. Will only be present when exporting "gl" loaders.
- profile: OpenGL profile to use. Default is chosen based on GL version. One of the following:
-		core:
-		compatibility:
- extensions: A table of OpenGL extensions to export.
- outname: The base filename of the file to create.
- style: A string containing the particular style of binding. This can be:
-		pointer-c: The default. The functions will be stored in pointers exposed to the user. #defines will be used to rename the pointers to the core GL function names.
-		pointer-c++: The functions will be stored in pointers, but the pointers and enumerators will be placed in the namespace "gl".
- prefix: A prefix to be added to the names of identifiers that must be global, while avoiding name clashes. This is useful if you want to have different sets of bindings to different APIs (like a GL 3.3 and 2.1 binding). Defaults to the empty string.
]]

local cmd = require "_CmdLineOptions"

local function FixupExtensionName(ext)
	return ext
end

local parseOpts = cmd.CreateOptionGroup()
parseOpts:enum(
	"spec",
	"spec",
	"Specification to use. One of the following:",
	{"gl", "glX", "wgl"},
	1)
parseOpts:value(
	"version",
	"version",
	{"OpenGL version to export.", "Only use this with the 'gl' spec."},
	nil,
	true)
parseOpts:enum(
	"profile",
	"profile",
	{"OpenGL profile to use.", "Only use this with the 'gl' spec."},
	{"core", "compatibility"},
	1,
	true)
parseOpts:enum(
	"style",
	"style",
	{"Export style."},
	{"pointer-c", "pointer-c++"},
	1)
parseOpts:array(
	"exts",
	"extensions",
	{"A list of extensions to export."},
	FixupExtensionName)
parseOpts:value(
	"prefix",
	"prefix",
	{
		"String to prefix to various globals. Set this to ",
		"prevent interference with multiple loaders."
	},
	"")
parseOpts:pos_opt(
	1,
	"outname",
	"Base filename (sans extension",
	"outname",
	nil,
	true)
	
function GetOptions(cmd_line)
	local options, pos_args = parseOpts:ProcessCmdLine(cmd_line)
	
	if(options.spec == "gl") then
		--Check version/profile.
		parseOpts:AssertParse(options.version, "You must specify an OpenGL version to export.")
	else
		parseOpts:AssertParse(not options.version, "Versions cannot be specified for wgl/glX")
		parseOpts:AssertParse(not options.profile, "Profiles cannot be specified for wgl/glX")
	end

	return options

--[[
	local options = {}
	
	local status, posOpts = 
		pcall(cmd.CmdLineOptions, cmd_line, procs, options)
		
	AssertParse(status, posOpts)

	AssertParse(posOpts[1], "You did not specify an output filename.")
	
	options.spec = options.spec or "gl"
	options.func_style = options.func_style or "pointer"
	options.language = options.language or "c"
	
	
	return options
	]]
end

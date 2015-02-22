--[[
    Copyright (C) 2014  absurdworlds
    
    License LGPLv3-only:
    GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.
--]]

function SetupSolution()
	solution "hrengin"
		configurations { "Debug", "Release"}
 
end

function SetupProject(prjname, ...)
	project(prjname)
		kind "SharedLib"
		language "C++"

		files { ... }

		libdirs { "../../lib", "../../dependencies/libs" }
		targetdir { "../../lib" }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			architecture "x86"
			architecture "x64"

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }

		configuration "vs*"
			defines { "_CRT_SECURE_NO_WARNINGS" }
			vpaths { ["Includes"] = "../../include/**" }
			vpaths { ["Sources"] = "**.cpp" }
			vpaths { ["Headers"] = "**.h" }
end

function SetupDefines(prjname, conf, ...)
	project(prjname)
		configuration(conf)
			defines { ... }
end

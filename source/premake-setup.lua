
function SetupSolution()
	solution "hrengin"
		configurations { "Debug", "Release" }
end

function SetupProject(prjname, ...)
	project(prjname)
		kind "ConsoleApp"
		language "C++"
		
		files { ... }

		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }

		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
	
		configuration "vs*"
			defines { "_CRT_SECURE_NO_WARNINGS" }
end
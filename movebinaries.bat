set solutiondir=%2
set sourcedir=%2\%1
set libdir=%2\lib
set gamedir=%2\..\Game\system
IF "%1" == "Debug" set target=debug
IF "%1" == "Release" set target=release

for %%f in (%sourcedir%\*.exe %sourcedir%\*.dll) do xcopy /y %%f %gamedir%\
for %%f in (%sourcedir%\*.lib %sourcedir%\*.exp) do xcopy /y %%f %libdir%\win32-msvc-%target%\

IF %errorlevel% == 0 exit
pause
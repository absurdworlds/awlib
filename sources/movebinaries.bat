set sourcedir=E:\RTSGame\Code\sources\%1
set gamedir=E:\RTSGame\Code\sources\%1
set targetdir=E:\RTSGame\Code\sources\%1
for %%f in (%sourcedir%\*.exe %sourcedir%\*.dll) do xcopy /y %%f E:\RTSGame\Game\system\
IF "%1" == "Debug" for %%f in (%sourcedir%\*.lib %sourcedir%\*.exp) do xcopy /y %%f E:\RTSGame\Code\lib\win32-msvc-debug\
IF "%1" == "Release" for %%f in (%sourcedir%\*.lib %sourcedir%\*.exp) do xcopy /y %%f E:\RTSGame\Code\lib\win32-msvc-release\

exit
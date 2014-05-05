set dir=%cd%\sources\Debug
for %%f in (%dir%\*.exe %dir%\*.dll) do move /y %%f .\..\Game\system\
for %%f in (%dir%\*.lib %dir%\*.exp) do move /y %%f %cd%\lib\msvc-win32-debug\
REM pause
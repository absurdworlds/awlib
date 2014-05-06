set dir=%cd%\Debug
for %%f in (%dir%\*.exe %dir%\*.dll) do move /y %%f E:\RTSGame\Game\system\
for %%f in (%dir%\*.lib %dir%\*.exp) do move /y %%f E:\RTSGame\Code\lib\msvc-win32-debug\
exit
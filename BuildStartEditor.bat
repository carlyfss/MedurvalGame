@echo off

call .\BuildVars.bat

call .\BuildProject.bat

start "" "%UE5EDITOR_EXE%" "%UPROJECT_PATH%" %*
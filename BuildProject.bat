@echo off

call .\BuildVars.bat

call "%BUILD_BAT%" %PROJECT_NAME%Editor Win64 Development "%UPROJECT_PATH%" -waitmutex -NoHotReload

@pause
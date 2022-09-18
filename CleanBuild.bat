@echo off
call .\BuildVars.bat

call "%UBT_PATH%" -ProjectFiles -UsePrecompiled -Game "%UPROJECT_PATH%"

@echo on

call .\BuildProject.bat

@pause
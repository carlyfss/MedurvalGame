set ROOTDIR=%~dp0
set ROOTDIR=%ROOTDIR:~0,-1%

set PROJECT_NAME=Medurval
set UPROJECT_PATH=%ROOTDIR%\%PROJECT_NAME%.uproject

set UE5_DIR=C:\Program Files\Epic Games\UE_5.0
set UE5EDITOR_EXE=%UE5_DIR%\Engine\Binaries\Win64\UnrealEditor.exe
set BUILD_BAT=%UE5_DIR%\Engine\Build\BatchFiles\Build.bat
set UBT_PATH=%UE5_DIR%\Engine\Binaries\DotNET\UnrealBuildTool\UnrealBuildTool.exe
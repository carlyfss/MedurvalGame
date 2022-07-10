@echo off
call .\BuildVars.bat

@RD /S /Q "./Binaries"
@RD /S /Q "./DerivedDataCache"
@RD /S /Q "./Intermediate"
@RD /S /Q "./Saved"
@RD /S /Q "./Script"
@RD /S /Q "./.vs"
@RD /S /Q "%COMMON_BASE_PLUGIN_DIR%\Binaries"
@RD /S /Q "%COMMON_BASE_PLUGIN_DIR%\Intermediate"
@RD /S /Q "%INVENTORY_PLUGIN_DIR%\Binaries"
@RD /S /Q "%INVENTORY_PLUGIN_DIR%\Intermediate"
@RD /S /Q "%SETTLEMENT_PLUGIN_DIR%\Binaries"
@RD /S /Q "%SETTLEMENT_PLUGIN_DIR%\Intermediate"
@RD /S /Q "%COMPASS_PLUGIN_DIR%\Binaries"
@RD /S /Q "%COMPASS_PLUGIN_DIR%\Intermediate"
@RD /S /Q "%COMMON_CURRENCY_PLUGIN_DIR%\Binaries"
@RD /S /Q "%COMMON_CURRENCY_PLUGIN_DIR%\Intermediate"

call "%UBT_PATH%" -ProjectFiles -UsePrecompiled -Game "%UPROJECT_PATH%"

@echo on

call .\BuildProject.bat

@pause
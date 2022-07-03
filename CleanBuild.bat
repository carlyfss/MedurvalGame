@echo off

call .\BuildVars.bat

@RD /S /Q "./Binaries"
@RD /S /Q "./DerivedDataCache"
@RD /S /Q "./Intermediate"
@RD /S /Q "./Saved"
@RD /S /Q "./Script"
@RD /S /Q "./.vs"
@RD /S /Q "./Plugins/GameFeatures/CommonBase/Binaries"
@RD /S /Q "./Plugins/GameFeatures/CommonBase/Intermediate"
@RD /S /Q "./Plugins/GameFeatures/InventoryManager/Binaries"
@RD /S /Q "./Plugins/GameFeatures/InventoryManager/Intermediate"
@RD /S /Q "./Plugins/GameFeatures/SettlementSystem/Binaries"
@RD /S /Q "./Plugins/GameFeatures/SettlementSystem/Intermediate"
@RD /S /Q "./Plugins/GameFeatures/RadarCompass/Binaries"
@RD /S /Q "./Plugins/GameFeatures/RadarCompass/Intermediate"

call "%UBT_PATH%" -ProjectFiles -UsePrecompiled -Game "%UPROJECT_PATH%"

@echo on

call .\BuildProject.bat
// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/MDPlayerController.h"

#include "Core/AssetManager/MedurvalAssetManager.h"

AMDPlayerController::AMDPlayerController()
{
}

void AMDPlayerController::LoadWidgets()
{
    FStreamableManager &StreamableManager = UAssetManager::GetStreamableManager();

    TArray<FSoftObjectPath> Objects;

    Objects.Add(CharacterWidgetClass.ToSoftObjectPath());
    Objects.Add(SettlementWidgetClass.ToSoftObjectPath());
    Objects.Add(BuildingsListWidgetClass.ToSoftObjectPath());

    StreamableManager.RequestAsyncLoad(Objects);
}

void AMDPlayerController::SetSettlementView(bool bIsOnSettlementView)
{
    bIsSettlementView = bIsOnSettlementView;
}

UCommonActivatableWidget *AMDPlayerController::GetSettlementWidget()
{
    return SettlementWidget;
}


// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/AssetManager/MedurvalAssetManager.h"

const FPrimaryAssetType UMedurvalAssetManager::DefaultItemType = TEXT("DefaultItem");
const FPrimaryAssetType UMedurvalAssetManager::ConsumableItemType = TEXT("ConsumableItem");
const FPrimaryAssetType UMedurvalAssetManager::ResourceItemType = TEXT("ResourceItem");
const FPrimaryAssetType UMedurvalAssetManager::SettlementBuildingType = TEXT("SettlementBuilding");
const FPrimaryAssetType UMedurvalAssetManager::WeaponItemType = TEXT("WeaponItem");
const FPrimaryAssetType UMedurvalAssetManager::EquipmentItemType = TEXT("EquipmentItem");

void UMedurvalAssetManager::StartInitialLoading()
{
    Super::StartInitialLoading();
}

UMedurvalAssetManager &UMedurvalAssetManager::Get()
{
    UMedurvalAssetManager *This = Cast<UMedurvalAssetManager>(GEngine->AssetManager);

    if (This)
    {
        return *This;
    }

    UE_LOG(LogTemp, Fatal, TEXT("Invalid asset manager in DefaultEngine.ini, must set to MedurvalAssetManager"))
    return *NewObject<UMedurvalAssetManager>();
}

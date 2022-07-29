// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Subsystems/SSSettlementSubsystem.h"

#include "Components/SSSettlementComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "GameFramework/Character.h"
#include "Subsystems/GameInstanceSubsystem.h"

void USSSettlementSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    UMedurvalAssetManager &AssetManager = UMedurvalAssetManager::Get();

    AssetManager.GetPrimaryAssetIdList(UMedurvalAssetManager::SettlementBuildingType, AllBuildings);

    if (AllBuildings.Num() > 0)
    {
        TArray<FName> LoadBundles;
        LoadBundles.Add(UMedurvalAssetManager::UIBundle);
        constexpr bool bIsRecursive = false;

        UE_LOG(LogTemp, Warning, TEXT("SettlementBuildings|UIBundle| Pre-load Started"))
        const FStreamableDelegate SettlementBuildingsDelegate = FStreamableDelegate::CreateUObject(this, &USSSettlementSubsystem::OnSettlementBuildingsLoaded);
        AssetManager.PreloadPrimaryAssets(AllBuildings, LoadBundles, bIsRecursive, SettlementBuildingsDelegate);
    }
}

void USSSettlementSubsystem::Deinitialize()
{
}

void USSSettlementSubsystem::OnSettlementBuildingsLoaded()
{
    UMedurvalAssetManager &AssetManager = UMedurvalAssetManager::Get();

    for (FPrimaryAssetId Building : AllBuildings)
    {
        USSBuildingDA *BuildingData = Cast<USSBuildingDA>(AssetManager.GetPrimaryAssetObject(Building));
        TPair<FPrimaryAssetId, ESSTerrainSize> BuildingMapValuePair = TPair<FPrimaryAssetId, ESSTerrainSize>(Building, BuildingData->Size);
        BuildingsMapBySize.Add(BuildingMapValuePair);
    }
}

USSSettlementComponent *USSSettlementSubsystem::GetSettlementByOwner(ACharacter *OwnerCharacter) const
{
    USSSettlementComponent *ReturnedSettlement = nullptr;

    for (USSSettlementComponent *Settlement : Settlements)
    {
        if (Settlement->GetSettlementOwner() == OwnerCharacter)
        {
            ReturnedSettlement = Settlement;
        }
    }

    return ReturnedSettlement;
}

TArray<USSSettlementComponent *> USSSettlementSubsystem::GetSettlements() const
{
    return Settlements;
}

void USSSettlementSubsystem::RegisterNewSettlement(USSSettlementComponent *Settlement)
{
    if (!Settlement)
        return;

    Settlements.Add(Settlement);
}

TMap<FPrimaryAssetId, ESSTerrainSize> USSSettlementSubsystem::GetBuildingsMapBySize() const
{
    return BuildingsMapBySize;
}

TArray<FPrimaryAssetId> USSSettlementSubsystem::GetAllBuildings() const
{
    return AllBuildings;
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Subsystems/STSettlementSubsystem.h"
#include "Components/STSettlementComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Actors/STTerrainActor.h"
#include "DataAssets/STBuildingDA.h"

void USTSettlementSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    UMedurvalAssetManager &AssetManager = UMedurvalAssetManager::Get();

    AssetManager.GetPrimaryAssetIdList(UMedurvalAssetManager::SettlementBuildingType, AllBuildings);

    if (AllBuildings.Num() > 0)
    {
        TArray<FName> LoadBundles;
        LoadBundles.Add(UMedurvalAssetManager::UIBundle);
        constexpr bool bIsRecursive = false;

        UE_LOG(LogTemp, Warning, TEXT("SettlementBuildings|UIBundle| Pre-load Started"))
        const FStreamableDelegate SettlementBuildingsDelegate = FStreamableDelegate::CreateUObject(this, &USTSettlementSubsystem::OnSettlementBuildingsLoaded);
        AssetManager.PreloadPrimaryAssets(AllBuildings, LoadBundles, bIsRecursive, SettlementBuildingsDelegate);
    }
}

void USTSettlementSubsystem::Deinitialize()
{
}

void USTSettlementSubsystem::OnSettlementBuildingsLoaded()
{
    UMedurvalAssetManager &AssetManager = UMedurvalAssetManager::Get();

    for (FPrimaryAssetId Building : AllBuildings)
    {
        USTBuildingDA *BuildingData = Cast<USTBuildingDA>(AssetManager.GetPrimaryAssetObject(Building));
        TPair<FPrimaryAssetId, ESTTerrainSize> BuildingMapValuePair = TPair<FPrimaryAssetId, ESTTerrainSize>(Building, BuildingData->Size);
        BuildingsMapBySize.Add(BuildingMapValuePair);
    }
}

USTSettlementComponent* USTSettlementSubsystem::GetSettlementByOwner(AMDCharacter* OwnerCharacter) const
{
    USTSettlementComponent *ReturnedSettlement = nullptr;

    for (USTSettlementComponent *Settlement : Settlements)
    {
        if (Settlement->GetSettlementOwner() == OwnerCharacter)
        {
            ReturnedSettlement = Settlement;
        }
    }

    return ReturnedSettlement;
}

TArray<USTSettlementComponent *> USTSettlementSubsystem::GetSettlements() const
{
    return Settlements;
}

void USTSettlementSubsystem::RegisterNewSettlement(USTSettlementComponent *Settlement)
{
    if (!Settlement)
        return;

    Settlements.Add(Settlement);
}

TMap<FPrimaryAssetId, ESTTerrainSize> USTSettlementSubsystem::GetBuildingsMapBySize() const
{
    return BuildingsMapBySize;
}

TArray<FPrimaryAssetId> USTSettlementSubsystem::GetAllBuildings() const
{
    return AllBuildings;
}

void USTSettlementSubsystem::AddNewTerrain(ASTTerrainActor *NewTerrain)
{
    if (NewTerrain)
    {
        AllTerrains.Add(NewTerrain);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Terrain is not valid!"));
    }
}

TArray<ASTTerrainActor *> USTSettlementSubsystem::GetAllTerrains() const
{
    return AllTerrains;
}

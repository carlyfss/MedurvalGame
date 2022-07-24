// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSBuildingActor.h"

#include "Components/CBStaticMeshComponent.h"
#include "Components/SSMaintenanceComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

ASSBuildingActor::ASSBuildingActor()
{
    Mesh = CreateDefaultSubobject<UCBStaticMeshComponent>("BuildingMesh");
    Maintenance = CreateDefaultSubobject<USSMaintenanceComponent>("MaintenanceComponent");
}

void ASSBuildingActor::LoadConfiguration()
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);
    BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASSBuildingActor::OnConfigurationLoaded);

    AssetManager->LoadPrimaryAsset(ConfigurationId, BundlesToLoad, Delegate);
}

void ASSBuildingActor::OnConfigurationLoaded()
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    ConfigurationReference = Cast<USSBuildingDA>(AssetManager->GetPrimaryAssetObject(ConfigurationId));

    if (!ConfigurationReference)
        return;

    if (ConfigurationReference->AvailableTiers.Num() > 0)
    {
        Tier = ConfigurationReference->AvailableTiers[0];
        Maintenance->SetDailyIncome(Tier.DailyIncome);
        Maintenance->SetDailyUpkeep(Tier.DailyUpkeep);
        Maintenance->SetCostToBuild(Tier.CostToBuild);

        UE_LOG(LogTemp, Warning, TEXT("Loaded..."))
    }
}

void ASSBuildingActor::TimerDelegate()
{
    Super::TimerDelegate();

    OnBeginConstruction_Implementation();
}

void ASSBuildingActor::OnBeginConstruction_Implementation()
{
    if (!ConfigurationReference)
    {
        TimerInterval = 0.5f;
        StartTimerWithDelegate();
    }

    UStaticMesh *StaticMesh = Tier.Mesh.Get();

    if (!StaticMesh)
        return;

    Mesh->SetStaticMesh(StaticMesh);
}

void ASSBuildingActor::OnConstructionCompleted()
{
}

void ASSBuildingActor::BeginPlay()
{
    Super::BeginPlay();

    if (ConfigurationId.IsValid())
    {
        LoadConfiguration();
        UE_LOG(LogTemp, Warning, TEXT("Loading Building..."))
    }
}

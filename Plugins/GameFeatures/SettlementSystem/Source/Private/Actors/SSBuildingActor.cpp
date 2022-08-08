// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSBuildingActor.h"

#include "Components/CBStaticMeshComponent.h"
#include "Components/SSMaintenanceComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/SSSettlementSubsystem.h"

ASSBuildingActor::ASSBuildingActor()
{
    Mesh = CreateDefaultSubobject<UCBStaticMeshComponent>("BuildingMesh");
    Mesh->SetupAttachment(RootComponent);
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
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("Building configuration did not have any tiers configured!"))
    }

    OnConfigurationLoadCompleted.Broadcast();
}

void ASSBuildingActor::OnConstructionCompleted()
{
    UStaticMesh *StaticMesh = GetMeshByCivilization(Civilization);

    if (StaticMesh)
    {
        Mesh->SetStaticMesh(StaticMesh);
    }

    const UMDGameInstance* GameInstance = Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    if (!GameInstance)
        return;

    USSSettlementSubsystem *Subsystem = GameInstance->GetSubsystem<USSSettlementSubsystem>();
    USSSettlementComponent* Settlement = Subsystem->GetSettlementByOwner(GameInstance->GetPlayerReference());

    if (Settlement)
    {
        Maintenance->EnableMaintenance(Settlement);    
    }
}

UStaticMesh* ASSBuildingActor::GetMeshByCivilization(ESSCivilizationType TargetCivilization) const
{
    UStaticMesh* BuildingMesh = nullptr;
    const bool bHasCivilizationMesh = Tier.CivilizationMesh.Contains(TargetCivilization);
        
    if (bHasCivilizationMesh)
    {
        BuildingMesh = Tier.CivilizationMesh.Find(TargetCivilization)->Get();
    }

    return BuildingMesh;
}

void ASSBuildingActor::BeginPlay()
{
    Super::BeginPlay();

    LoadConfiguration();
}

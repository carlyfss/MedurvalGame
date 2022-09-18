// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/STBuildingActor.h"

#include "Components/STMaintenanceComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Components/MDStaticMeshComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Core/Singletons/MDGameMode.h"
#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/STSettlementSubsystem.h"

ASTBuildingActor::ASTBuildingActor()
{
    MaintenanceComponent = CreateDefaultSubobject<USTMaintenanceComponent>("MaintenanceComponent");
    ConstructionComponent = CreateDefaultSubobject<USTConstructionComponent>("ConstructionComponent");

    Mesh = CreateDefaultSubobject<UMDStaticMeshComponent>("BuildingMesh");
    Mesh->SetupAttachment(RootComponent);
    Mesh->SetVisibility(false);
}

ESTCivilizationType ASTBuildingActor::GetCivilization()
{
    return Civilization;
}

void ASTBuildingActor::SetBuildingMesh(UStaticMesh *NewMesh) const
{
    Mesh->SetStaticMesh(NewMesh);
}

void ASTBuildingActor::LoadConfiguration()
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);
    BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASTBuildingActor::OnConfigurationLoaded);

    AssetManager->LoadPrimaryAsset(ConfigurationId, BundlesToLoad, Delegate);
}

void ASTBuildingActor::OnConfigurationLoaded()
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    ConfigurationReference = Cast<USTBuildingDA>(AssetManager->GetPrimaryAssetObject(ConfigurationId));

    if (!ConfigurationReference)
        return;

    if (ConfigurationReference->AvailableTiers.Num() > 0)
    {
        Tier = ConfigurationReference->AvailableTiers[0];

        MaintenanceComponent->SetDailyIncome(Tier.DailyIncome);
        MaintenanceComponent->SetDailyUpkeep(Tier.DailyUpkeep);
        MaintenanceComponent->SetCostToBuild(Tier.CostToBuild);
    } else
    {
        UE_LOG(LogTemp, Warning, TEXT("Building configuration did not have any tiers configured!"))
    }

    ConstructionComponent->SetBuildingTier(Tier);
    ConstructionComponent->SetConstructionSiteTransform(this->GetActorLocation(), this->GetActorRotation());

    FindConstructionMeshes();

    ConstructionComponent->OnUpdateConstructionStep.AddDynamic(this, &ASTBuildingActor::ASTBuildingActor::UpdateBuildingConstructionMesh);
    ConstructionComponent->OnConstructionCompleted.AddDynamic(this, &ASTBuildingActor::OnConstructionCompleted);
    
    OnConfigurationLoadCompleted.Broadcast();
}

void ASTBuildingActor::FindConstructionMeshes()
{
    for (FSTBuildingConstructionMeshes ConstructionMeshes : Tier.ConstructionMeshes)
    {
        if (ConstructionMeshes.Civilization == GetCivilization())
        {
            ConstructionComponent->SetConstructionMeshes(ConstructionMeshes.Meshes);
        }
    }
}

void ASTBuildingActor::CheckMeshVisibility() const
{
    if (!Mesh->IsVisible())
    {
        Mesh->SetVisibility(true);
    }
}

void ASTBuildingActor::UpdateBuildingConstructionMesh(int Index)
{
    UStaticMesh *NewMesh = ConstructionComponent->GetConstructionMeshAtIndex(Index);

    if (NewMesh)
    {
        Mesh->SetStaticMesh(NewMesh);
        CheckMeshVisibility();
    }
}

void ASTBuildingActor::OnConstructionCompleted()
{
    UStaticMesh *StaticMesh = GetMeshByCivilization(Civilization);

    if (StaticMesh)
    {
        Mesh->SetStaticMesh(StaticMesh);
        CheckMeshVisibility();
    }

    const UMDGameInstance* GameInstance = Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

    if (!GameInstance)
        return;

    USTSettlementSubsystem *Subsystem = GameInstance->GetSubsystem<USTSettlementSubsystem>();

    AMDGameMode* GameMode = Cast<AMDGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

    USTSettlementComponent* Settlement = Subsystem->GetSettlementByOwner(GameMode->GetPlayerReference());

    if (Settlement)
    {
        MaintenanceComponent->EnableMaintenance(Settlement);
    }
}

UStaticMesh* ASTBuildingActor::GetMeshByCivilization(ESTCivilizationType TargetCivilization) const
{
    UStaticMesh* BuildingMesh = nullptr;
    const bool bHasCivilizationMesh = Tier.CivilizationMesh.Contains(TargetCivilization);
        
    if (bHasCivilizationMesh)
    {
        BuildingMesh = Tier.CivilizationMesh.Find(TargetCivilization)->Get();
    }

    return BuildingMesh;
}

void ASTBuildingActor::BeginPlay()
{
    Super::BeginPlay();

    LoadConfiguration();
}

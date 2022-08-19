// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSBuildingActor.h"

#include "Components/CBStaticMeshComponent.h"
#include "Components/SSMaintenanceComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/SSSettlementSubsystem.h"

void ASSBuildingActor::StartConstructionTimer()
{
    ConstructionMeshesLength = ConstructionMeshes.Num();
    CurrentTime += 1;

    const FTimerDelegate CountdownDelegate = FTimerDelegate::CreateUObject(this, &ASSBuildingActor::TimerCountdown); 
    GetWorld()->GetTimerManager().SetTimer(ConstructionTimerHandle, CountdownDelegate, 1.f, true, 0.f);
}

void ASSBuildingActor::TimerCountdown()
{
    CurrentTime -= 1;
    OnUpdateConstructionTime.Broadcast(CurrentTime);
    
    UpdateConstructionProgress();
    const int ConstructionPercentage = CurrentTime / Tier.ConstructionDuration;
    OnUpdateConstructionPercentage.Broadcast(ConstructionPercentage);
    
    if (CurrentTime > 0)
        return;

    GetWorld()->GetTimerManager().ClearTimer(ConstructionTimerHandle);
    ConstructionTimerHandle.Invalidate();
    OnConstructionCompleted();
}

void ASSBuildingActor::UpdateConstructionProgress()
{
    const int UpdateSteps = Tier.ConstructionDuration / ConstructionMeshes.Num();
    const int TimeForNextStep = UpdateSteps * ConstructionMeshesLength;

    if (TimeForNextStep != CurrentTime)
        return;

    ChangeConstructionStep(CurrentStep);
    CurrentStep += 1;
    ConstructionMeshesLength -= 1;
}

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

    CurrentTime = Tier.ConstructionDuration;
    
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

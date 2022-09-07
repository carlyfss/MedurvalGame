// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STConstructionComponent.h"
#include "Actors/STConstructionSiteActor.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

USTConstructionComponent::USTConstructionComponent()
{
}

void USTConstructionComponent::SetConstructionResources()
{
    if (ConstructionResources.Num() < 1)
    {
        TArray<FPrimaryAssetId> ItemsIds;
        TArray<int> ItemsQuantities;

        BuildingTier.Requirements.Resources.GenerateKeyArray(ItemsIds);
        BuildingTier.Requirements.Resources.GenerateValueArray(ItemsQuantities);

        for (int i = 0; i < ItemsIds.Num(); i++)
        {
            FSTConstructionResource NewResource = FSTConstructionResource();

            NewResource.Item = ItemsIds[i];
            NewResource.TargetAmount = ItemsQuantities[i];

            ConstructionResources.Add(NewResource);
        }
    }
}

void USTConstructionComponent::SpawnConstructionSite()
{
    if (!ConstructionSite)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        ConstructionSite = GetWorld()->SpawnActor<ASTConstructionSiteActor>(ConstructionSiteClass.Get(), BuildingLocation, BuildingRotation, SpawnParameters);
    }
}

bool USTConstructionComponent::IsRequiredResourcesFilled()
{
    bool bAreAllResourcesFilled = false;

    if (ConstructionResources.Num() > 0)
    {
        int FilledResourceCount = 0;

        for (FSTConstructionResource Resource : ConstructionResources)
        {
            if (Resource.CurrentAmount == Resource.TargetAmount)
            {
                FilledResourceCount++;
            }
        }

        if (FilledResourceCount == ConstructionResources.Num())
        {
            bAreAllResourcesFilled = true;
        }
    }

    return bAreAllResourcesFilled;
}

void USTConstructionComponent::LoadConstructionSite()
{
    FStreamableManager &StreamableManager = UMedurvalAssetManager::GetStreamableManager();

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &USTConstructionComponent::OnConstructionSiteLoaded);
    StreamableManager.RequestAsyncLoad(ConstructionSiteClass.ToSoftObjectPath(), Delegate);
}

void USTConstructionComponent::OnConstructionSiteLoaded()
{
    if (ConstructionSiteClass.Get())
    {
        SpawnConstructionSite();
    }
}

void USTConstructionComponent::FinishConstruction()
{
    GetWorld()->GetTimerManager().ClearTimer(ConstructionTimerHandle);
    ConstructionTimerHandle.Invalidate();
    OnConstructionCompleted.Broadcast();
    bIsConstructionComplete = true;

    ConstructionSite->Destroy();
    ConstructionSite = nullptr;
}

TObjectPtr<UStaticMesh> USTConstructionComponent::GetConstructionMeshAtIndex(int Index)
{
    UStaticMesh *Mesh = nullptr;

    if (Index < ConstructionMeshes.Num())
    {
        Mesh = ConstructionMeshes[Index].Get();
    }

    return Mesh;
}

void USTConstructionComponent::SetConstructionMeshes(TArray<TSoftObjectPtr<UStaticMesh>> Meshes)
{
    ConstructionMeshes = Meshes;
    ConstructionMeshesLength = ConstructionMeshes.Num();
}

void USTConstructionComponent::SetBuildingTier(FSTBuildingTier Tier)
{
    BuildingTier = Tier;
}

void USTConstructionComponent::SetConstructionSiteTransform(FVector Location, FRotator Rotation)
{
    BuildingLocation = Location;
    BuildingRotation = Rotation;
}

void USTConstructionComponent::AddResource(FPrimaryAssetId Resource, uint8 Amount)
{
    for (int i = 0; i < ConstructionResources.Num(); i++)
    {
        FSTConstructionResource ConstructionResource = ConstructionResources[i];
        if (ConstructionResource.Item == Resource)
        {
            int NewAmount = NewAmount = ConstructionResource.CurrentAmount + Amount;
            ConstructionResources[i].CurrentAmount = NewAmount;
            break;
        }
    }
}

bool USTConstructionComponent::StartConstructionTimer()
{
    bool bIsConstructionStarted = false;
    bIsConstructionComplete = false;
    CurrentTime = BuildingTier.ConstructionDuration + 1;
    LoadConstructionSite();
    SetConstructionResources();
    OnTryStartConstruction.Broadcast();

    if (IsRequiredResourcesFilled())
    {
        const FTimerDelegate CountdownDelegate = FTimerDelegate::CreateUObject(this, &USTConstructionComponent::TimerCountdown);
        GetWorld()->GetTimerManager().SetTimer(ConstructionTimerHandle, CountdownDelegate, 1.f, true, 0.f);
        bIsConstructionStarted = true;
        bIsConstructionOccurring = true;
    }

    return bIsConstructionStarted;
}

void USTConstructionComponent::TimerCountdown()
{
    CurrentTime -= 1;
    OnUpdateConstructionTime.Broadcast(CurrentTime);

    UpdateConstructionProgress();
    const int ConstructionPercentage = CurrentTime / BuildingTier.ConstructionDuration;
    OnUpdateConstructionPercentage.Broadcast(ConstructionPercentage);

    if (CurrentTime > 0)
    {
        return;
    }

    FinishConstruction();
}

void USTConstructionComponent::UpdateConstructionProgress()
{
    const int UpdateSteps = BuildingTier.ConstructionDuration / ConstructionMeshes.Num();
    const int TimeForNextStep = UpdateSteps * ConstructionMeshesLength;

    if (TimeForNextStep != CurrentTime)
    {
        return;
    }

    OnUpdateConstructionStep.Broadcast(CurrentStep);
    CurrentStep += 1;
    ConstructionMeshesLength -= 1;
}

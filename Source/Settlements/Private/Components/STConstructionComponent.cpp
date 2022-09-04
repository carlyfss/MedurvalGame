// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STConstructionComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

USTConstructionComponent::USTConstructionComponent()
{
}

void USTConstructionComponent::SetCurrentTime(int Time)
{
    CurrentTime = Time;
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

void USTConstructionComponent::StartConstructionTimer()
{
    CurrentTime += 1;

    const FTimerDelegate CountdownDelegate = FTimerDelegate::CreateUObject(this, &USTConstructionComponent::TimerCountdown);
    GetWorld()->GetTimerManager().SetTimer(ConstructionTimerHandle, CountdownDelegate, 1.f, true, 0.f);
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

    GetWorld()->GetTimerManager().ClearTimer(ConstructionTimerHandle);
    ConstructionTimerHandle.Invalidate();
    OnConstructionCompleted.Broadcast();
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

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/CBActorComponent.h"
#include "Structs/STBuildingTier.h"
#include "STConstructionComponent.generated.h"

class ASTBuildingActor;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="ConstructionComponent"))
class USTConstructionComponent : public UCBActorComponent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    TArray<TSoftObjectPtr<UStaticMesh>> ConstructionMeshes;

    UPROPERTY(BlueprintReadWrite, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    int CurrentTime = 0;

    uint8 CurrentStep = 0;

    uint8 ConstructionMeshesLength = 0;

    FSTBuildingTier BuildingTier;

protected:
    FTimerHandle ConstructionTimerHandle;

    UFUNCTION(BlueprintCallable, Category="ConstructionComponent")
    void StartConstructionTimer();

    void TimerCountdown();

    void UpdateConstructionProgress();

public:
    USTConstructionComponent();

    void SetCurrentTime(int Time);

    TObjectPtr<UStaticMesh> GetConstructionMeshAtIndex(int Index);
    void SetConstructionMeshes(TArray<TSoftObjectPtr<UStaticMesh>> Meshes);

    void SetBuildingTier(FSTBuildingTier Tier);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionPercentage, float, Percentage);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionPercentage OnUpdateConstructionPercentage;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionTime, int, Time);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionTime OnUpdateConstructionTime;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionStep, int, Index);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionStep OnUpdateConstructionStep;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConstructionCompleted);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnConstructionCompleted OnConstructionCompleted;
};

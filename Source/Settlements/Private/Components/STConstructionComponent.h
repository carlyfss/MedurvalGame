// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "Structs/STBuildingTier.h"
#include "Structs/STConstructionResource.h"
#include "STConstructionComponent.generated.h"

class ASTBuildingActor;
class ASTConstructionSiteActor;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="ConstructionComponent"))
class USTConstructionComponent : public UMDActorComponent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    TArray<TSoftObjectPtr<UStaticMesh>> ConstructionMeshes;

    UPROPERTY(BlueprintReadWrite, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    int CurrentTime = 0;

    UPROPERTY(BlueprintReadOnly, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    bool bIsConstructionOccurring = false;

    UPROPERTY(BlueprintReadOnly, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    bool bIsConstructionComplete = false;
    
    uint8 CurrentStep = 0;

    uint8 ConstructionMeshesLength = 0;

    FSTBuildingTier BuildingTier;

    UPROPERTY(BlueprintReadOnly, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    TArray<FSTConstructionResource> ConstructionResources;

    FVector BuildingLocation;

    FRotator BuildingRotation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ConstructionComponent", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASTConstructionSiteActor> ConstructionSiteClass;

    TObjectPtr<ASTConstructionSiteActor> ConstructionSite;

protected:
    FTimerHandle ConstructionTimerHandle;

    UFUNCTION(BlueprintCallable, Category="ConstructionComponent")
    bool StartConstructionTimer();

    void TimerCountdown();

    void UpdateConstructionProgress();

    void SetConstructionResources();

    void SpawnConstructionSite();

    UFUNCTION(BlueprintCallable, Category="ConstructionComponent")
    bool IsRequiredResourcesFilled();

    void LoadConstructionSite();

    void OnConstructionSiteLoaded();

    void FinishConstruction();
    
public:
    USTConstructionComponent();

    TObjectPtr<UStaticMesh> GetConstructionMeshAtIndex(int Index);
    void SetConstructionMeshes(TArray<TSoftObjectPtr<UStaticMesh>> Meshes);

    void SetBuildingTier(FSTBuildingTier Tier);

    void SetConstructionSiteTransform(FVector Location, FRotator Rotation);

    UFUNCTION(BlueprintCallable, Category="ConstructionComponent")
    void AddResource(FPrimaryAssetId Resource, uint8 Amount);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionPercentage, float, Percentage);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionPercentage OnUpdateConstructionPercentage;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionTime, int, Time);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionTime OnUpdateConstructionTime;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionStep, int, Index);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionStep OnUpdateConstructionStep;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTryStartConstruction);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnTryStartConstruction OnTryStartConstruction;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConstructionCompleted);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnConstructionCompleted OnConstructionCompleted;
};

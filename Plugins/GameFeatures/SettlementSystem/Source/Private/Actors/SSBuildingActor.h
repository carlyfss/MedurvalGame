// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Base/SSActor.h"
#include "DataAssets/SSBuildingDA.h"
#include "Structs/SSBuildingTier.h"
#include "SSBuildingActor.generated.h"

class UCBStaticMeshComponent;
class USSBuildingTierComponent;
class USSMaintenanceComponent;
class USSSettlementComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="BuildingActor"))
class ASSBuildingActor : public ASSActor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FPrimaryAssetId ConfigurationId;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSBuildingDA> ConfigurationReference = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FSSBuildingTier Tier = FSSBuildingTier();

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    ESSCivilizationType Civilization = ESSCivilizationType::Human;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    USSMaintenanceComponent *Maintenance = nullptr;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBStaticMeshComponent> Mesh = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    int CurrentTime = 0;

    uint8 CurrentStep = 0;

    uint8 ConstructionMeshesLength = 0;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TArray<TSoftObjectPtr<UStaticMesh>> ConstructionMeshes;

protected:
    void LoadConfiguration();

    void OnConfigurationLoaded();

    FTimerHandle ConstructionTimerHandle;

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void StartConstructionTimer();

    void TimerCountdown();

    void UpdateConstructionProgress();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void ChangeConstructionStep(int Index);

public:
    ASSBuildingActor();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionPercentage, float, Percentage);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionPercentage OnUpdateConstructionPercentage;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionTime, int, Time);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionTime OnUpdateConstructionTime;
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfigurationLoadCompleted);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnConfigurationLoadCompleted OnConfigurationLoadCompleted;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void OnBeginConstruction();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void OnConstructionCompleted();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    UStaticMesh* GetMeshByCivilization(ESSCivilizationType TargetCivilization) const;

    virtual void BeginPlay() override;
};

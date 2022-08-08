// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
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
    TArray<TSoftObjectPtr<UStaticMesh>> ConstructionMeshes;

public:
    ASSBuildingActor();

    void LoadConfiguration();

    void OnConfigurationLoaded();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionStep, float, Percentage);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionStep OnUpdateConstructionStep;
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfigurationLoadCompleted);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnConfigurationLoadCompleted OnConfigurationLoadCompleted;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void OnBeginConstruction();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void ChangeConstructionStep(int Index);

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void OnConstructionCompleted();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    UStaticMesh* GetMeshByCivilization(ESSCivilizationType TargetCivilization) const;

    virtual void BeginPlay() override;
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Actors/CBActor.h"
#include "DataAssets/SSBuildingDA.h"
#include "Enums/SSBuildingType.h"
#include "Structs/SSBuildingTier.h"
#include "SSBuildingActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateConstructionStep, float, Percentage);

class UCBStaticMeshComponent;
class USSBuildingTierComponent;
class USSMaintenanceComponent;
class USSSettlementComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="BuildingActor"))
class ASSBuildingActor : public ACBActor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FPrimaryAssetId ConfigurationId;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSBuildingDA> ConfigurationReference = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FSSBuildingTier Tier = FSSBuildingTier();

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    USSMaintenanceComponent *Maintenance = nullptr;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBStaticMeshComponent> Mesh = nullptr;

public:
    ASSBuildingActor();

    void LoadConfiguration();

    void OnConfigurationLoaded();

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateConstructionStep OnUpdateConstructionStep;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void OnBeginConstruction();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void OnConstructionCompleted();

    virtual void BeginPlay() override;
};

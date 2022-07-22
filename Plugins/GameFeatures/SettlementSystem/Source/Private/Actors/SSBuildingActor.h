// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Actors/CBActor.h"
#include "Enums/SSBuildingType.h"
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
class ASSBuildingActor : public ACBActor
{
    GENERATED_BODY()

#pragma region Configurations
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FGameplayTag SizeTag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FName Name = FName("BuildingName");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    ESSBuildingType Type = ESSBuildingType::Civilian;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    bool bHasTiers = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TArray<FSSBuildingTier> AvailableTiers;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FSSBuildingTier CurrentTier;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    USSMaintenanceComponent *Maintenance;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    bool bIsAvailableToBuild = false;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    bool bIsUnderConstruction = false;
#pragma endregion Configurations

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    USSSettlementComponent *AssignedSettlement;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBStaticMeshComponent> Mesh;

public:
    ASSBuildingActor();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void OnBeginConstruction();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void OnConstructionCompleted();

    virtual void BeginPlay() override;
};

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
/**
 * 
 */
UCLASS(meta=(DisplayName="BuildingActor"))
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
    FText Description = FText::FromName("Building description.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    ESSBuildingType Type = ESSBuildingType::Civilian;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    bool bHasTiers = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TArray<FSSBuildingTier> AvailableTiers;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FSSBuildingTier CurrentTier;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    USSMaintenanceComponent *Maintenance;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    bool bIsAvailableToBuild = false;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    bool bIsUnderConstruction = false;
#pragma endregion Configurations

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBStaticMeshComponent> Mesh;

public:
    ASSBuildingActor();
};

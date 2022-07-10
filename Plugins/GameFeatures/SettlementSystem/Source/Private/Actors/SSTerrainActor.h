// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SSBuildingActor.h"
#include "Actors/CBActor.h"
#include "Enums/SSTerrainSize.h"
#include "Enums/SSTerrainStatus.h"
#include "SSTerrainActor.generated.h"

UCLASS(meta=(DisplayName="TerrainActor"))
class ASSTerrainActor : public ACBActor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESSTerrainSize Size = ESSTerrainSize::Small;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESSTerrainStatus Status = ESSTerrainStatus::Unclaimed;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TArray<TSoftClassPtr<ASSBuildingActor>> AvailableBuildings;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASSBuildingActor> AssignedBuilding;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASSBuildingActor> ConstructedBuilding;
};

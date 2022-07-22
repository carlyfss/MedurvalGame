// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SSBuildingActor.h"
#include "Actors/CBActor.h"
#include "Enums/SSTerrainSize.h"
#include "Enums/SSTerrainStatus.h"
#include "SSTerrainActor.generated.h"

UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="TerrainActor"))
class ASSTerrainActor : public ACBActor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESSTerrainSize Size = ESSTerrainSize::Small;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESSTerrainStatus Status = ESSTerrainStatus::Unclaimed;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASSBuildingActor> AssignedBuilding;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASSBuildingActor> ConstructedBuilding;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    float Width = 400.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    float Length = 400.f;

public:
    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SetAssignedBuilding(TSoftClassPtr<ASSBuildingActor> Building);

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SetConstructedBuilding(ASSBuildingActor *Building);
};

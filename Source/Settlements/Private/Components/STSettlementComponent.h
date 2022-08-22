// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "STSettlementEconomyComponent.h"
#include "Actors/STTerrainActor.h"
#include "Components/CBActorComponent.h"
#include "Enums/STSettlementStages.h"
#include "Enums/STCivilizationType.h"
#include "Structs/STSettlementStage.h"
#include "STSettlementComponent.generated.h"

/**
 * 
 */
UCLASS()
class USTSettlementComponent : public UCBActorComponent
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    FName Name = FName("SettlementName");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    ESTCivilizationType Type = ESTCivilizationType::Human;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    float InfluenceRadius = 2000;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    ESTSettlementStages CurrentStage = ESTSettlementStages::Camp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    TArray<FSTSettlementStage> Stages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    TArray<ASTTerrainActor *> OwnedTerrains;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementEconomyComponent> Economy;

    TObjectPtr<ACharacter> Owner;

public:
    USTSettlementComponent();
    
    UFUNCTION(BlueprintCallable, Category="SettlementComponent")
    void SetSettlementOwner(ACharacter *SettlementOwner);

    UFUNCTION(BlueprintCallable, Category="SettlementComponent")
    ACharacter *GetSettlementOwner() const;

    USTSettlementEconomyComponent *GetEconomy() const;

    bool AddNewTerrain(ASTTerrainActor *Terrain);

    virtual void BeginPlay() override;
};

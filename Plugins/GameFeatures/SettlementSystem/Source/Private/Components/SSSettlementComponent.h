// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SSSettlementEconomyComponent.h"
#include "Actors/SSTerrainActor.h"
#include "Components/CBActorComponent.h"
#include "Enums/SSSettlementStages.h"
#include "Enums/SSSettlementType.h"
#include "Structs/SSSettlementStage.h"
#include "SSSettlementComponent.generated.h"

/**
 * 
 */
UCLASS()
class USSSettlementComponent : public UCBActorComponent
{
    GENERATED_BODY()

    USSSettlementComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    FName Name = FName("SettlementName");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    ESSSettlementType Type = ESSSettlementType::Humans;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    float InfluenceRadius = 2000;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    ESSSettlementStages CurrentStage = ESSSettlementStages::Camp;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    TArray<FSSSettlementStage> Stages;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    TArray<ASSTerrainActor *> OwnedTerrains;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="SettlementComponent", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementEconomyComponent> Economy;

    TObjectPtr<ACharacter> Owner;

public:
    UFUNCTION(BlueprintCallable, Category="SettlementComponent")
    void SetSettlementOwner(ACharacter *SettlementOwner);

    UFUNCTION(BlueprintCallable, Category="SettlementComponent")
    ACharacter *GetSettlementOwner() const;

    USSSettlementEconomyComponent *GetEconomy();

    virtual void BeginPlay() override;
};

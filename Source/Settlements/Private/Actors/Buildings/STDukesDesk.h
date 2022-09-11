// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/STBuildingActor.h"
#include "STDukesDesk.generated.h"

class UMDBoxComponent;
class UMDSphereComponent;
class ASTEaglesViewPawn;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="DukesDesk"))
class ASTDukesDesk : public ASTBuildingActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementComponent> SettlementComponent = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASTEaglesViewPawn> EaglesViewActorClass;

    UPROPERTY(BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASTEaglesViewPawn> EaglesViewActor;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    int StartingTreasury = 1000;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSphereComponent> SettlementSizeCollision;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBoxComponent> SettlementRangeCollision;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBoxComponent> DeskCollision;

    UPROPERTY(BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TArray<ASTTerrainActor *> OverlappedTerrains;

    UPROPERTY(BlueprintReadWrite, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UDecalComponent> SettlementSizeDecal = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMaterialInterface> SettlementSizeDecalMaterial = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMaterialInstanceDynamic> SettlementSizeDecalMaterialInstance = nullptr;

protected:
    void CreateEaglesViewActor();

    void RegisterSettlement();

    void FinishSettlementConfiguration();

    UFUNCTION(BlueprintCallable, Category="DukesDesk")
    void PossessEaglesViewActor();

    UFUNCTION(BlueprintCallable, Category="DukesDesk")
    void PossessCharacterActor();

    void GetAndShowTerrainsInSettlementRange();

    void ShowTerrainsInRange();

    void HideTerrainsInRange();

    void SetClaimableTerrainsInSettlementSize();

    void SpawnSettlementSizeDecal();
    
public:
    ASTDukesDesk();

    UFUNCTION(BlueprintCallable, Category="DukesDesk")
    void UpdateSettlementRangeAndSize();

    virtual void BeginPlay() override;
};

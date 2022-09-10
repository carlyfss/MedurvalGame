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

    UPROPERTY(BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDSphereComponent> SettlementSizeCollision;

    UPROPERTY(BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBoxComponent> SettlementRangeCollision;

    UPROPERTY(BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBoxComponent> DeskCollision;

    UPROPERTY(BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TArray<ASTTerrainActor *> OverlappedActors;

protected:
    void CreateEaglesViewActor();

    void RegisterSettlement();
    
public:
    ASTDukesDesk();

    UFUNCTION(BlueprintCallable, Category="DukesDesk")
    void UpdateSettlementRangeAndSize();

    virtual void BeginPlay() override;
};

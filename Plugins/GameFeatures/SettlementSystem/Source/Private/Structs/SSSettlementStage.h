// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "SSSettlementRequirements.h"
#include "SSSettlementStage.generated.h"

class ASSBuildingActor;
class UStaticMesh;

USTRUCT(BlueprintType, meta = (DisplayName = "SettlementStage"))
struct SETTLEMENTSYSTEM_API FSSSettlementStage
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    FName Name = FName("Stage Name");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    FText Description = FText::FromName("Stage description.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    TObjectPtr<UTexture2D> Icon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    uint8 ConstructionDuration;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    FText UnlockablesDescription = FText::FromName("Decription of what the tier unlocks.");

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Unlockableitems;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    TArray<TSoftClassPtr<ASSBuildingActor>> UnlockableBuildings;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementStage", meta=(AllowPrivateAccess=true))
    FSSSettlementRequirements Requirements;
};

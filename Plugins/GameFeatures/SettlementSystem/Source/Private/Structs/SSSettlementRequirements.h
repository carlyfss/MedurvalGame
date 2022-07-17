// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "SSSettlementRequirements.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "SettlementRequirements"))
struct SETTLEMENTSYSTEM_API FSSSettlementRequirements
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementRequirements", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Items;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementRequirements", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Resources;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="SettlementRequirements", meta=(AllowPrivateAccess=true))
    TMap<FName, FText> CustomAttributes;
};

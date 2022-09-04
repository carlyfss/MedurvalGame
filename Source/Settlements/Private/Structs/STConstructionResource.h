// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "STConstructionResource.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "ConstructionResource"))
struct SETTLEMENTS_API FSTConstructionResource
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ConstructionResource", meta=(AllowPrivateAccess=true))
    FPrimaryAssetId Item;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ConstructionResource", meta=(AllowPrivateAccess=true))
    int CurrentAmount;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ConstructionResource", meta=(AllowPrivateAccess=true))
    int TargetAmount;
};

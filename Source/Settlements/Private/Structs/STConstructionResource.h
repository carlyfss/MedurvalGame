// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "STConstructionResource.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "ConstructionResource"))
struct SETTLEMENTS_API FSTConstructionResource
{
    GENERATED_BODY()

    int MAX_RESOURCE_AMOUNT = 500;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ConstructionResource", meta=(AllowPrivateAccess=true))
    FPrimaryAssetId Item;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ConstructionResource", meta=(AllowPrivateAccess=true))
    int CurrentAmount = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="ConstructionResource", meta=(AllowPrivateAccess=true))
    int TargetAmount = 0;

    FSTConstructionResource();

    bool IsFilled() const;
};

inline FSTConstructionResource::FSTConstructionResource()
{
    CurrentAmount = 0;
    TargetAmount = 0;
}

inline bool FSTConstructionResource::IsFilled() const
{
    return CurrentAmount == TargetAmount;
}

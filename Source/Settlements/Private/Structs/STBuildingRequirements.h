// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "STBuildingRequirements.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingRequirements"))
struct SETTLEMENTS_API FSTBuildingRequirements
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingRequirements", meta=(AllowPrivateAccess=true))
    TMap<FPrimaryAssetId, int> Items;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingRequirements", meta=(AllowPrivateAccess=true))
    TMap<FPrimaryAssetId, int> Resources;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingRequirements", meta=(AllowPrivateAccess=true))
    TMap<FName, FText> CustomAttributes;
};

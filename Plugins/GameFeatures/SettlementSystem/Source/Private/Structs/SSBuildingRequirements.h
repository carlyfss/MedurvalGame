// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "SSBuildingRequirements.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "BuildingRequirements"))
struct SETTLEMENTSYSTEM_API FSSBuildingRequirements
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingRequirements", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Items;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingRequirements", meta=(AllowPrivateAccess=true))
    TArray<FPrimaryAssetId> Resources;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="BuildingRequirements", meta=(AllowPrivateAccess=true))
    TMap<FName, FText> CustomAttributes;
};

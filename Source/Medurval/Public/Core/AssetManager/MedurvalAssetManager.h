// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MedurvalAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMedurvalAssetManager final : public UAssetManager
{
    GENERATED_BODY()

public:
    virtual void StartInitialLoading() override;

    // Return the asset manager singleton class
    static UMedurvalAssetManager &Get();

    static const FPrimaryAssetType DefaultItemType;
    static const FPrimaryAssetType ConsumableItemType;
    static const FPrimaryAssetType ResourceItemType;
    static const FPrimaryAssetType EquipmentItemType;
    static const FPrimaryAssetType AccessoryItemType;
    static const FPrimaryAssetType WeaponItemType;
    static const FPrimaryAssetType SettlementBuildingType;

    inline static const FName WorldBundle = "World";
    inline static const FName UIBundle = "UI";
    inline static const FName MandatoryBundle = "Mandatory";
};

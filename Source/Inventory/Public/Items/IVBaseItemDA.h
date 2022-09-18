// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/DataAssets/MDPrimaryDataAsset.h"
#include "Enums/IVItemCategories.h"
#include "Enums/IVItemRarity.h"
#include "Interfaces/IVUsableItemInterface.h"
#include "IVBaseItemDA.generated.h"

class UStaticMesh;
class UTexture2D;
/**
 * 
 */
UCLASS(meta=(DisplayName="BaseItemDA"))
class INVENTORY_API UIVBaseItemDA : public UMDPrimaryDataAsset, public IIVUsableItemInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
    FText Name = FText::FromString(TEXT("Item"));

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
    FText Description = FText::FromString(TEXT("Item description"));

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
    TSoftObjectPtr<UStaticMesh> Mesh = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item")
    TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(DisplayName="Category"))
    EIVItemCategories Category = EIVItemCategories::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(DisplayName="Rarity"))
    EIVItemRarity Rarity = EIVItemRarity::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be stacked?"))
    int Value = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be used?"))
    bool bCanBeUsed = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be stacked?"))
    bool bCanBeStacked = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Item", meta=(DisplayName="On 'Use' Event text"))
    FText OnUseText = FText::FromString(TEXT(""));

#pragma region FUNCTIONS
    UFUNCTION()
    virtual void UseItem_Implementation(AActor *ItemOwner) override;
#pragma endregion FUNCTIONS

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

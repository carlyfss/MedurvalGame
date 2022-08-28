// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/MDBaseDataAsset.h"
#include "Enums/IVItemCategories.h"
#include "Interfaces/IVUsableItemInterface.h"
#include "IVBaseItemDA.generated.h"

class UStaticMesh;
class UTexture2D;
/**
 * 
 */
UCLASS(meta=(DisplayName="BaseItemDA"))
class INVENTORY_API UIVBaseItemDA : public UMDBaseDataAsset, public IIVUsableItemInterface
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    FText Name = FText::FromString(TEXT("Item"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
    FText Description = FText::FromString(TEXT("Item description"));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AssetBundles = "World"))
    TSoftObjectPtr<UStaticMesh> Mesh = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(AssetBundles = "UI"))
    TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="Category"))
    EIVItemCategories Category = EIVItemCategories::None;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="On 'Use' Event text"))
    FText OnUseText = FText::FromString(TEXT(""));

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be used?"))
    bool bCanBeUsed = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be stacked?"))
    bool bCanBeStacked = false;

#pragma region FUNCTIONS
    UFUNCTION()
    virtual void UseItem_Implementation(AActor *ItemOwner) override;
#pragma endregion FUNCTIONS

    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

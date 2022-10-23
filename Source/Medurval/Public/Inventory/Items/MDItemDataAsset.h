// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/DataAssets/MDPrimaryDataAsset.h"
#include "Inventory/Enums/MDItemCategories.h"
#include "Inventory/Enums/MDItemRarity.h"
#include "Inventory/Interfaces/MDUsableItemInterface.h"
#include "MDItemDataAsset.generated.h"

class UStaticMesh;
class UTexture2D;
/**
 * 
 */
UCLASS(meta=(DisplayName="MDItemDataAsset"))
class MEDURVAL_API UMDItemDataAsset : public UMDPrimaryDataAsset, public IMDUsableItemInterface
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset")
	FText Name = FText::FromString(TEXT("Item"));

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset")
	FText Description = FText::FromString(TEXT("Item description"));

	/**
	 * Mesh used for the pickup object.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(AssetBundles="World,Mandatory"))
	TSoftObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(AssetBundles="UI,Mandatory"))
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(DisplayName="Category"))
	EMDItemCategories Category = EMDItemCategories::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(DisplayName="Rarity"))
	EMDItemRarity Rarity = EMDItemRarity::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset")
	int Value = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(DisplayName="Item can be used?"))
	bool bCanBeUsed = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset",
		meta=(DisplayName="Item can be stacked?"))
	bool bCanBeStacked = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset",
		meta=(DisplayName="On 'Use' Event text"))
	FText OnUseText = FText::FromString(TEXT(""));

#pragma region FUNCTIONS
	UFUNCTION()
	virtual void UseItem_Implementation(AActor* ItemOwner) override;
#pragma endregion FUNCTIONS

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

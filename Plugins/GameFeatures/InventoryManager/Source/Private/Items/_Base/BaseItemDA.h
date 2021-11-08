// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/EItemCategories.h"
#include "BaseItemDA.generated.h"

UCLASS(meta = (DisplayName = "InventoryItemDataAsset"))
class INVENTORYMANAGER_API UBaseItemDA : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText Name = FText::FromString(TEXT("Rock"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float Weight = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText Description = FText::FromString(TEXT("Just a rock"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSoftObjectPtr<UStaticMesh> ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="On 'Use' Event text"))
	FText OnUseText = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be used?"))
	bool bCanBeUsed = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item", meta=(DisplayName="Item can be stacked?"))
	bool bCanBeStacked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	EItemCategories Category = EItemCategories::Resource;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("DefaultItem", GetFName());
	}
};

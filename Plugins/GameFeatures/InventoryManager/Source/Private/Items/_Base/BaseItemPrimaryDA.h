// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Enums/EIMItemCategories.h"
#include "Interfaces/IMUsableItemInterface.h"
#include "BaseItemPrimaryDA.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="InventoryItemPrimaryDA"))
class UBaseItemPrimaryDA : public UPrimaryDataAsset, public IIMUsableItemInterface
{
	GENERATED_BODY()

public:
	
	// Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item")
	FText Name = FText::FromString(TEXT("Rock"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item")
	float Weight = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item")
	FText Description = FText::FromString(TEXT("Just a rock"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item")
	TSoftObjectPtr<UStaticMesh> ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item", meta=(DisplayName="On 'Use' Event text"))
	FText OnUseText = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item")
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item", meta=(DisplayName="Item can be used?"))
	bool bCanBeUsed = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item", meta=(DisplayName="Item can be stacked?"))
	bool bCanBeStacked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="_Item")
	EIMItemCategories Category = EIMItemCategories::Resource;

	// Functions
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

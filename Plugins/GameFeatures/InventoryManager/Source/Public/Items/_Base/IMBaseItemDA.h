// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/MDBaseDataAsset.h"
#include "Enums/EIMItemCategories.h"
#include "Interfaces/IMUsableItemInterface.h"
#include "IMBaseItemDA.generated.h"

class UIMInventoryComponent;
/**
 * 
 */
UCLASS(meta=(DisplayName="InventoryItemDA"))
class UIMBaseItemDA : public UMDBaseDataAsset, public IIMUsableItemInterface
{
	GENERATED_BODY()

	TObjectPtr<UIMInventoryComponent> OwnerInventoryComponent = nullptr;

	uint8 IndexAtInventory;

	UPROPERTY(BlueprintGetter=GetItemMesh, Category="Inventory Item|Getters")
	TObjectPtr<UStaticMesh> ItemStaticMesh = nullptr;

	UPROPERTY(BlueprintGetter=GetItemThumbnail, Category="Inventory Item|Getters")
	TObjectPtr<UTexture2D> ItemThumbnail = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintSetter=SetIsItemLoaded, BlueprintGetter=GetIsItemLoaded,
		Category="Inventory Item")
	bool bIsItemLoaded = false;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item")
	FText Name = FText::FromString(TEXT("Item"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item")
	FText Description = FText::FromString(TEXT("Item description"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item", meta=(DisplayName="Item Category"))
	EIMItemCategories Category = EIMItemCategories::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item", meta=(DisplayName="On 'Use' Event text"))
	FText OnUseText = FText::FromString(TEXT(""));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item", meta=(DisplayName="Item can be used?"))
	bool bCanBeUsed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item", meta=(DisplayName="Item can be stacked?"))
	bool bCanBeStacked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item")
	float Weight = 0.1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item")
	TSoftObjectPtr<UStaticMesh> ItemMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Inventory Item")
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

#pragma region FUNCTIONS

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Getters")
	UStaticMesh* GetItemMesh() const;

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Getters")
	UTexture2D* GetItemThumbnail() const;

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Getters")
	TSoftObjectPtr<UTexture2D> GetThumbnail() const;

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Getters")
	bool GetIsItemLoaded() const;

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Setters")
	void SetIsItemLoaded(bool bIsLoaded);

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Setters")
	void SetOwnerInventoryComponent(UIMInventoryComponent* OwnerInventory);

	UFUNCTION(BlueprintCallable, Category="Inventory Item|Setters")
	void SetIndexAtInventory(uint8 Index);

	UFUNCTION()
	void SetLoadedItemAssets(AActor* ObjectOwner);

	UFUNCTION()
	void UnloadItemAssets();

	UFUNCTION()
	virtual void UseItem_Implementation(AActor* ItemOwner) override;

#pragma endregion FUNCTIONS

protected:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

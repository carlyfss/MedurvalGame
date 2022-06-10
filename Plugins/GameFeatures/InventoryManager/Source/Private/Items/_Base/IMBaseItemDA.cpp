// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Items/_Base/IMBaseItemDA.h"

#include "Components/IMInventoryComponent.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Interfaces/IMUsableItemInterface.h"
#include "UI/_Base/IMInventorySlotWidget.h"
#include "UI/_Base/IMInventoryWidget.h"

UStaticMesh* UIMBaseItemDA::GetItemMesh() const
{
	return ItemStaticMesh;
}

UTexture2D* UIMBaseItemDA::GetItemThumbnail() const
{
	return ItemThumbnail;
}

TSoftObjectPtr<UTexture2D> UIMBaseItemDA::GetThumbnail() const
{
	return Thumbnail;
}

bool UIMBaseItemDA::GetIsItemLoaded() const
{
	return bIsItemLoaded;
}

void UIMBaseItemDA::SetIsItemLoaded(bool bIsLoaded)
{
	bIsItemLoaded = bIsLoaded;
}

void UIMBaseItemDA::SetOwnerInventoryComponent(UIMInventoryComponent* OwnerInventory)
{
	OwnerInventoryComponent = OwnerInventory;
}

void UIMBaseItemDA::SetIndexAtInventory(uint8 Index)
{
	IndexAtInventory = Index;
}

FPrimaryAssetId UIMBaseItemDA::GetPrimaryAssetId() const
{
	return FPrimaryAssetId("InventoryDefaultItem", GetFName());
}

void UIMBaseItemDA::SetLoadedItemAssets(AActor* ObjectOwner)
{
	SetDataAssetOwner(ObjectOwner);

	ItemThumbnail = this->Thumbnail.Get();

	SetIsItemLoaded(true);
}

void UIMBaseItemDA::UnloadItemAssets()
{
	SetIsItemLoaded(false);
	ItemStaticMesh = nullptr;
	ItemThumbnail = nullptr;
}

void UIMBaseItemDA::UseItem_Implementation(AActor* ItemOwner)
{
	IIMUsableItemInterface::UseItem_Implementation(ItemOwner);
}

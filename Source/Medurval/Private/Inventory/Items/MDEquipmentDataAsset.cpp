// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDEquipmentDataAsset.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Inventory/Components/MDInventoryComponent.h"

void UMDEquipmentDataAsset::UnequipItemAtAttachment(AMDEnhancedCharacter* Character)
{
	Character->UnequipItem(Attachment);

	UMDInventoryComponent* Inventory = Cast<UMDInventoryComponent>(
		Character->GetComponentByClass(UMDInventoryComponent::StaticClass()));

	if (Inventory)
	{
		Inventory->UnequipItem(Attachment);
	}
}

void UMDEquipmentDataAsset::EquipItemAtAttachment(AMDEnhancedCharacter* Character)
{
	Character->EquipItem(Attachment, GetPrimaryAssetId());

	UMDInventoryComponent* Inventory = Cast<UMDInventoryComponent>(
		Character->GetComponentByClass(UMDInventoryComponent::StaticClass()));

	if (Inventory)
	{
		Inventory->EquipItem(Attachment, GetPrimaryAssetId());
	}
}

FPrimaryAssetId UMDEquipmentDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::EquipmentItemType, GetFName());
}

void UMDEquipmentDataAsset::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);

	AMDEnhancedCharacter* Character = Cast<AMDEnhancedCharacter>(ItemOwner);

	if (Character)
	{
		if (!Character->IsSlotEquipped(Attachment))
		{
			EquipItemAtAttachment(Character);
		}
		else
		{
			UnequipItemAtAttachment(Character);
		}
	}
}

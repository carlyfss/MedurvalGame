// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDEquipableItemDataAsset.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Inventory/Components/MDInventoryComponent.h"

void UMDEquipableItemDataAsset::UnequipItemAtAttachment(AMDEnhancedCharacter* Character)
{
	UMDInventoryComponent* Inventory = Cast<UMDInventoryComponent>(
		Character->GetComponentByClass(UMDInventoryComponent::StaticClass()));

	if (Inventory)
	{
		if (GetEquipmentAttachment() != EMDEquipmentAttachment::None)
		{
			Inventory->UnequipItem(GetEquipmentAttachment());
		}

		if (GetAccessoryAttachment() != EMDAccessoryAttachment::None)
		{
			Inventory->UnequipItem(GetAccessoryAttachment());
		}

		if (GetWeaponAttachment() != EMDWeaponAttachment::None)
		{
			Inventory->UnequipItem(GetWeaponAttachment());
		}
	}
}

void UMDEquipableItemDataAsset::EquipItemAtAttachment(AMDEnhancedCharacter* Character)
{
	UMDInventoryComponent* Inventory = Cast<UMDInventoryComponent>(
		Character->GetComponentByClass(UMDInventoryComponent::StaticClass()));

	if (Inventory)
	{
		if (GetEquipmentAttachment() != EMDEquipmentAttachment::None)
		{
			Inventory->EquipItem(GetEquipmentAttachment(), GetPrimaryAssetId());
		}

		if (GetAccessoryAttachment() != EMDAccessoryAttachment::None)
		{
			Inventory->EquipItem(GetAccessoryAttachment(), GetPrimaryAssetId());
		}

		if (GetWeaponAttachment() != EMDWeaponAttachment::None)
		{
			Inventory->EquipItem(GetWeaponAttachment(), GetPrimaryAssetId());
		}
	}
}

void UMDEquipableItemDataAsset::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);

	bool bHasEquipped = false;
	AMDEnhancedCharacter* Character = Cast<AMDEnhancedCharacter>(ItemOwner);

	if (Character)
	{
		if (GetEquipmentAttachment() != EMDEquipmentAttachment::None)
		{
			if (!Character->IsSlotEquipped(GetEquipmentAttachment()))
			{
				EquipItemAtAttachment(Character);
				bHasEquipped = true;
			}
		}

		if (GetAccessoryAttachment() != EMDAccessoryAttachment::None)
		{
			if (!Character->IsSlotEquipped(GetAccessoryAttachment()))
			{
				EquipItemAtAttachment(Character);
				bHasEquipped = true;
			}
		}

		if (GetWeaponAttachment() != EMDWeaponAttachment::None)
		{
			if (!Character->IsSlotEquipped(GetWeaponAttachment()))
			{
				EquipItemAtAttachment(Character);
				bHasEquipped = true;
			}
		}


		if (!bHasEquipped)
		{
			UnequipItemAtAttachment(Character);
			EquipItemAtAttachment(Character);
		}
	}
}

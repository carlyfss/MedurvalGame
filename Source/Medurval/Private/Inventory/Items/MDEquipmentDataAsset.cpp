// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDEquipmentDataAsset.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

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
		Character->EquipItem(EMDEquipmentAttachment::Chest, GetPrimaryAssetId());
	}
}

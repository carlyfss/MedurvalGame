// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Items/MDWeaponDataAsset.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

FPrimaryAssetId UMDWeaponDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(UMedurvalAssetManager::WeaponItemType, GetFName());
}

bool UMDWeaponDataAsset::IsTwoHanded() const
{
	bool bIsTwoHanded = false;

	if (CombatStyle == EMDCombatStyles::DualWield)
	{
		bIsTwoHanded = true;
	}

	if (CombatStyle == EMDCombatStyles::TwoHanded)
	{
		bIsTwoHanded = true;
	}

	if (CombatStyle == EMDCombatStyles::BowAndArrow)
	{
		bIsTwoHanded = true;
	}

	if (CombatStyle == EMDCombatStyles::TwoHanded)
	{
		bIsTwoHanded = true;
	}

	if (CombatStyle == EMDCombatStyles::MagicalTwoHanded)
	{
		bIsTwoHanded = true;
	}

	return bIsTwoHanded;
}

EMDWeaponAttachment UMDWeaponDataAsset::GetWeaponAttachment()
{
	return Attachment;
}

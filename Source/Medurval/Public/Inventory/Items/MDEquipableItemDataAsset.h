// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "Inventory/Enums/MDAccessoryAttachment.h"
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "MDEquipableItemDataAsset.generated.h"

class AMDEnhancedCharacter;
/**
 * 
 */
UCLASS(meta=(DisplayName="MDEquipableItemDataAsset"))
class MEDURVAL_API UMDEquipableItemDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

	void UnequipItemAtAttachment(AMDEnhancedCharacter* Character);

	void EquipItemAtAttachment(AMDEnhancedCharacter* Character);

public:
	/**
	 * Mesh used to be equipped on the character. This mesh should not be used in Sockets on the character skeleton.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEquipableItemDataAsset",
		meta=(AssetBundles="World,Mandatory"))
	TSoftObjectPtr<USkeletalMesh> EquipableMesh = nullptr;

	virtual EMDEquipmentAttachment GetEquipmentAttachment()
	{
		return EMDEquipmentAttachment::None;
	}

	virtual EMDAccessoryAttachment GetAccessoryAttachment()
	{
		return EMDAccessoryAttachment::None;
	}

	virtual EMDWeaponAttachment GetWeaponAttachment()
	{
		return EMDWeaponAttachment::None;
	}

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

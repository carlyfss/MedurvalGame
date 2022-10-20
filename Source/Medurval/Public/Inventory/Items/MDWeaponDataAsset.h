// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDEquipableItemDataAsset.h"
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "MDWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDWeaponDataAsset"))
class MEDURVAL_API UMDWeaponDataAsset : public UMDEquipableItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDWeaponDataAsset", meta=(DisplayName="Attachment"))
	EMDWeaponAttachment Attachment = EMDWeaponAttachment::None;

	/**
	 * Mesh used in the Socket on the character skeleton to display the Weapon's mesh.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDWeaponDataAsset", meta=(AssetBundles="World"))
	TSoftObjectPtr<UStaticMesh> WeaponEquipableMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDWeaponDataAsset")
	int PhysicalDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDWeaponDataAsset")
	int MagicalDamage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDWeaponDataAsset")
	TArray<FText> BonusEffects = TArray<FText>();

	virtual EMDWeaponAttachment GetWeaponAttachment() override;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

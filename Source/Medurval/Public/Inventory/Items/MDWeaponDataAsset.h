// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDWeaponDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDWeaponDataAsset"))
class MEDURVAL_API UMDWeaponDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDWeaponDataAsset", meta=(DisplayName="Attachment"))
	EMDWeaponAttachment Attachment = EMDWeaponAttachment::None;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

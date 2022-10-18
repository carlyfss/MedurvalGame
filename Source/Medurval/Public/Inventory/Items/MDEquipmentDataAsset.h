// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDEquipableItemDataAsset.h"
#include "Core/Components/MDSkeletalMeshComponent.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDEquipmentDataAsset.generated.h"

class AMDEnhancedCharacter;
/**
 * 
 */
UCLASS(meta=(DisplayName="MDEquipmentDataAsset"))
class MEDURVAL_API UMDEquipmentDataAsset : public UMDEquipableItemDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEquipmentDataAsset", meta=(DisplayName="Attachment"))
	EMDEquipmentAttachment Attachment = EMDEquipmentAttachment::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEquipmentDataAsset")
	int PhysicalDefense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEquipmentDataAsset")
	int MagicalDefense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEquipmentDataAsset")
	TArray<FText> BonusEffects = TArray<FText>();

	virtual EMDEquipmentAttachment GetEquipmentAttachment() override;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

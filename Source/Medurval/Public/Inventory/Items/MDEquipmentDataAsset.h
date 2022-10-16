// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDSkeletalMeshComponent.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "MDEquipmentDataAsset.generated.h"

class AMDEnhancedCharacter;
/**
 * 
 */
UCLASS(meta=(DisplayName="MDEquipmentDataAsset"))
class MEDURVAL_API UMDEquipmentDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

	void UnequipItemAtAttachment(AMDEnhancedCharacter* Character);

	void EquipItemAtAttachment(AMDEnhancedCharacter* Character);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(AssetBundles="World"))
	TSoftObjectPtr<USkeletalMesh> EquipmentMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset", meta=(DisplayName="Attachment"))
	EMDEquipmentAttachment Attachment = EMDEquipmentAttachment::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset")
	int PhysicalDefense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset")
	int MagicalDefense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDItemDataAsset")
	TArray<FText> BonusEffects = TArray<FText>();
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

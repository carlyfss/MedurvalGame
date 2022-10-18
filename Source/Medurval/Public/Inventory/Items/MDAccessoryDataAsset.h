// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDEquipableItemDataAsset.h"
#include "Core/Actors/Characters/MDEnhancedCharacter.h"
#include "MDAccessoryDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDAcessoryDataAsset"))
class MEDURVAL_API UMDAccessoryDataAsset : public UMDEquipableItemDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDAcessoryDataAsset", meta=(DisplayName="Attachment"))
	EMDAccessoryAttachment Attachment = EMDAccessoryAttachment::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDAcessoryDataAsset")
	int PhysicalDefense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDAcessoryDataAsset")
	int MagicalDefense = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDAcessoryDataAsset")
	TArray<FText> BonusEffects = TArray<FText>();

	virtual EMDAccessoryAttachment GetAccessoryAttachment() override;
	
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

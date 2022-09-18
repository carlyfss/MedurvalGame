// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDItemDataAsset.h"
#include "Inventory/Enums/MDConsumableEffectType.h"
#include "MDConsumableDataAsset.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="MDConsumableDataAsset"))
class MEDURVAL_API UMDConsumableDataAsset : public UMDItemDataAsset
{
	GENERATED_BODY()

public:
	// Effects are going to be GameplayEffect / Abilities 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MDConsumableDataAsset")
	float Effect = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MDConsumableDataAsset")
	float Duration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MDConsumableDataAsset")
	bool bIsInstantUsage = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MDConsumableDataAsset")
	float UsageDuration = 2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MDConsumableDataAsset")
	EMDConsumableEffectType EffectType = EMDConsumableEffectType::None;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

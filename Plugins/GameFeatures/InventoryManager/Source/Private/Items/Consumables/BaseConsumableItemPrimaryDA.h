// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Enums/EIMConsumableEffectType.h"
#include "Items/_Base/BaseItemPrimaryDA.h"
#include "BaseConsumableItemPrimaryDA.generated.h"

/**
 * 
 */
UCLASS()
class UBaseConsumableItemPrimaryDA : public UBaseItemPrimaryDA
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float HealthAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float DamageAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float Duration = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	bool bIsInstantUsage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	EIMConsumableEffectType EffectType = EIMConsumableEffectType::Buff;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

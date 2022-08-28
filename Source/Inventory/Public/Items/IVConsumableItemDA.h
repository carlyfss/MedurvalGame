// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Enums/IVConsumableEffectType.h"
#include "Items/IVBaseItemDA.h"
#include "IVConsumableItemDA.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="ConsumableItemDA"))
class INVENTORY_API UIVConsumableItemDA : public UIVBaseItemDA
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float HealthAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float DamageAmount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float Duration = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	bool bIsInstantUsage = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	EIVConsumableEffectType EffectType = EIVConsumableEffectType::None;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

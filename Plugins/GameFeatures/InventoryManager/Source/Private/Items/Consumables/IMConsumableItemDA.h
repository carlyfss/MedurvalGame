// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Enums/EIMConsumableEffectType.h"
#include "Items/_Base/IMBaseItemDA.h"
#include "IMConsumableItemDA.generated.h"

/**
 * 
 */
UCLASS()
class UIMConsumableItemDA : public UIMBaseItemDA
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
	EIMConsumableEffectType EffectType = EIMConsumableEffectType::None;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

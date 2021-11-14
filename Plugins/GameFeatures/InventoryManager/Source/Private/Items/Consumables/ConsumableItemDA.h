// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Enums/EConsumableEffectType.h"
#include "Items/_Base/BaseItemDA.h"
#include "Macros/PrintString.h"
#include "ConsumableItemDA.generated.h"

/**
 * 
 */
UCLASS()
class UConsumableItemDA : public UBaseItemDA
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float HealthAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float DamageAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	float Duration = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	bool bIsInstantUsage = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item|Consumable")
	EConsumableEffectType EffectType = EConsumableEffectType::Buff;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Consumable", GetFName());
	}

	virtual void UseItem_Implementation(AActor* ItemOwner) override;
};

inline void UConsumableItemDA::UseItem_Implementation(AActor* ItemOwner)
{
	Super::UseItem_Implementation(ItemOwner);
	
	print("You used a consumable item");
}

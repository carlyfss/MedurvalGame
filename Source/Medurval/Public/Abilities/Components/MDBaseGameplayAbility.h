// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/Enums/EMDGameplayAbilityInputID.h"
#include "MDBaseGameplayAbility.generated.h"

/**
 * Base Gameplay Ability class for use in the Gameplay Ability System
 */
UCLASS(meta = (DisplayName = "MedurvalBaseGameplayAblity"))
class MEDURVAL_API UMDBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UMDBaseGameplayAbility();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Ability")
	EMDGameplayAbilityInputID AbilityInputID = EMDGameplayAbilityInputID::None;
};

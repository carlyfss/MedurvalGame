// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "MedurvalGameplayAbilityInputID"))
enum class EMDGameplayAbilityInputID : uint8
{
	None,
	Confirm,
	Cancel,
	Attack,
	Defend
};

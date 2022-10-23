// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "MDCombatStyles"))
enum class EMDCombatStyles : uint8
{
	None,
	Fist,
	OneHanded,
	OneHandedShield,
	BowAndArrow,
	TwoHanded,
	DualWield,
	MagicalOneHanded,
	MagicalTwoHanded
};

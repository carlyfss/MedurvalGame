// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "Item Categories"))
enum class EItemCategories : uint8
{
	Consumable,
	Weapon,
	Equipment,
	Resource,
	Skill,
	Accessory,
	Quest
};

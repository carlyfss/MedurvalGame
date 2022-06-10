﻿// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "Item Categories"))
enum class EIMItemCategories : uint8
{
	None,
	Consumable,
	Weapon,
	Equipment,
	Resource,
	Skill,
	Accessory,
	Quest
};

﻿// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

UENUM(BlueprintType, meta = (DisplayName = "ItemCategories"))
enum class EMDItemCategories : uint8
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

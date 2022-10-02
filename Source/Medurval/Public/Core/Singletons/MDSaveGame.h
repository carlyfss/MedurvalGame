// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Inventory/Structs/MDInventoryEquipmentSlot.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "MDSaveGame.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class MEDURVAL_API UMDSaveGame : public USaveGame
{
	GENERATED_BODY()

protected:
	virtual void Serialize(FArchive& Ar) override;

public:
	UMDSaveGame()
	{
	}

	UPROPERTY(BlueprintReadWrite, Category = SaveGame)
	TArray<FMDInventorySlot> InventorySlots = TArray<FMDInventorySlot>();

	UPROPERTY(BlueprintReadWrite, Category = SaveGame)
	TArray<FMDInventoryEquipmentSlot> EquipmentSlots = TArray<FMDInventoryEquipmentSlot>();
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDGameInstance.h"
#include "MDSaveGame.h"
#include "GameFramework/PlayerState.h"
#include "MDPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API AMDPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = SaveGame)
    TArray<FMDInventorySlot> InventorySlots = TArray<FMDInventorySlot>();

    void LoadSaveGame(UMDSaveGame* SavedGame);

    void CreateSaveGame(UMDSaveGame* SaveGame);
};

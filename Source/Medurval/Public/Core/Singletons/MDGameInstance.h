// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Inventory/Structs/MDInventorySlot.h"
#include "MDGameInstance.generated.h"

class USaveGame;
class UMDSaveGame;
class UMedurvalAssetManager;
class UMDEconomyComponent;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	/** List of inventory items to add to new players */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Inventory)
	TArray<FMDInventorySlot> DefaultInventory;

	/** The current save game object */
	UPROPERTY()
	UMDSaveGame* CurrentSaveGame;

	/** Rather it will attempt to actually save to disk */
	UPROPERTY()
	bool bSavingEnabled;

	/** True if we are in the middle of doing a save */
	UPROPERTY()
	bool bCurrentlySaving;

	/** True if another save was requested during a save */
	UPROPERTY()
	bool bPendingSaveRequested;

	/** Called when the async save happens */
	virtual void HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bIsSuccess);
    
public:
	UMDGameInstance();

	UFUNCTION(BlueprintCallable, Category="MDGameInstance")
	static UObject* GetPrimaryAssetIdObject(FPrimaryAssetId AssetId);

	template <class T>
	static FORCEINLINE T* GetCastPrimaryAssetId(FPrimaryAssetId AssetId)
	{
		return Cast<T>(GetPrimaryAssetIdObject(AssetId));
	}

	static void LoadObject(TSoftObjectPtr<> ObjectToLoad, FStreamableDelegate DelegateToCall = FStreamableDelegate());

	static void LoadClass(TSoftClassPtr<> ClassToLoad, FStreamableDelegate DelegateToCall = FStreamableDelegate());

	static void LoadPrimaryAssetId(FPrimaryAssetId AssetId, FStreamableDelegate DelegateToCall = FStreamableDelegate(),
	                               TArray<FName> BundlesToLoad = TArray<FName>());

	virtual void Init() override;

	/** The slot name used for saving */
	UPROPERTY(BlueprintReadWrite, Category = Save)
	FString SaveSlot;

	/** The platform-specific user index */
	UPROPERTY(BlueprintReadWrite, Category = Save)
	int32 SaveUserIndex;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoaded, UMDSaveGame*, SaveGame);

	/** Delegate called when the save game has been loaded/reset */
	UPROPERTY(BlueprintAssignable, Category = Inventory)
	FOnSaveGameLoaded OnSaveGameLoaded;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnSaveGameLoadedNative, UMDSaveGame*);

	/** Native delegate for save game load/reset */
	FOnSaveGameLoadedNative OnSaveGameLoadedNative;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDGameInstance")
	UMedurvalAssetManager* GetMedurvalAssetManager() const;

	UFUNCTION(BlueprintCallable, Category = Save)
	UMDSaveGame* GetCurrentSaveGame();

	/** Sets rather save/load is enabled. If disabled it will always count as a new character */
	UFUNCTION(BlueprintCallable, Category = Save)
	void SetSavingEnabled(bool bEnabled);

	/** Synchronously loads a save game. If it fails, it will create a new one for you. Returns true if it loaded, false if it created one */
	UFUNCTION(BlueprintCallable, Category = Save)
	bool LoadSaveGame();

	void CreateSaveGame();

	/** Handle the final setup required after loading a USaveGame object using AsyncLoadGameFromSlot. Returns true if it loaded, false if it created one */
	UFUNCTION(BlueprintCallable, Category = Save)
	bool HandleSaveGameLoaded(USaveGame* SaveGameObject);

	/** Gets the save game slot and user index used for inventory saving, ready to pass to GameplayStatics save functions */
	UFUNCTION(BlueprintCallable, Category = Save)
	void GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const;

	/** Writes the current save game object to disk. The save to disk happens in a background thread*/
	UFUNCTION(BlueprintCallable, Category = Save)
	bool WriteSaveGame();

	/** Resets the current save game to it's default. This will erase player data! This won't save to disk until the next WriteSaveGame */
	UFUNCTION(BlueprintCallable, Category = Save)
	void ResetSaveGame(); 
};

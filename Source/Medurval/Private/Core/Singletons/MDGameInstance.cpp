// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDGameInstance.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singletons/MDPlayerState.h"
#include "Core/Singletons/MDSaveGame.h"
#include "Kismet/GameplayStatics.h"

UMDGameInstance::UMDGameInstance()
    : SaveSlot(TEXT("SaveGame"))
      , SaveUserIndex(0)
{
}

void UMDGameInstance::HandleAsyncSave(const FString& SlotName, const int32 UserIndex, bool bIsSuccess)
{
    ensure(bCurrentlySaving);
    bCurrentlySaving = false;

    if (bPendingSaveRequested)
    {
        // Start another save as we got a request while saving
        bPendingSaveRequested = false;
        WriteSaveGame();
    }
}

UMedurvalAssetManager* UMDGameInstance::GetMedurvalAssetManager() const
{
    UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
    {
        UE_LOG(LogTemp, Error, TEXT("MedurvalAssetManager not available!"));
        return nullptr;
    }

    return AssetManager;
}

UMDSaveGame* UMDGameInstance::GetCurrentSaveGame()
{
    return CurrentSaveGame;
}

void UMDGameInstance::SetSavingEnabled(bool bEnabled)
{
    bSavingEnabled = bEnabled;
}

bool UMDGameInstance::LoadSaveGame()
{
    bool bHasLoaded = false;

    if (UGameplayStatics::DoesSaveGameExist(SaveSlot, SaveUserIndex) && bSavingEnabled)
    {
        UMDSaveGame* LoadedSave = nullptr;
        LoadedSave = Cast<UMDSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlot, SaveUserIndex));
        bHasLoaded = HandleSaveGameLoaded(LoadedSave);
    }

    return bHasLoaded;
}

void UMDGameInstance::CreateSaveGame()
{
    CurrentSaveGame = Cast<UMDSaveGame>(UGameplayStatics::CreateSaveGameObject(UMDSaveGame::StaticClass()));

    AMDPlayerState* PlayerState = Cast<AMDPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));
    PlayerState->CreateSaveGame(CurrentSaveGame);

    HandleAsyncSave(SaveSlot, SaveUserIndex, true);
}

bool UMDGameInstance::HandleSaveGameLoaded(USaveGame* SaveGameObject)
{
    bool bLoaded = false;

    if (!bSavingEnabled)
    {
        // If saving is disabled, ignore passed in object
        SaveGameObject = nullptr;
    }

    // Replace current save, old object will GC out
    CurrentSaveGame = Cast<UMDSaveGame>(SaveGameObject);
    AMDPlayerState* PlayerState = Cast<AMDPlayerState>(UGameplayStatics::GetPlayerState(GetWorld(), 0));

    if (CurrentSaveGame)
    {
        PlayerState->LoadSaveGame(CurrentSaveGame);
        bLoaded = true;
    }

    OnSaveGameLoaded.Broadcast(CurrentSaveGame);
    OnSaveGameLoadedNative.Broadcast(CurrentSaveGame);

    return bLoaded;
}

void UMDGameInstance::GetSaveSlotInfo(FString& SlotName, int32& UserIndex) const
{
    SlotName = SaveSlot;
    UserIndex = SaveUserIndex;
}

bool UMDGameInstance::WriteSaveGame()
{
    if (bSavingEnabled)
    {
        if (bCurrentlySaving)
        {
            // Schedule another save to happen after current one finishes. We only queue one save
            bPendingSaveRequested = true;
            return true;
        }

        // Indicate that we're currently doing an async save
        bCurrentlySaving = true;

        // This goes off in the background
        UGameplayStatics::AsyncSaveGameToSlot(GetCurrentSaveGame(), SaveSlot, SaveUserIndex,
                                              FAsyncSaveGameToSlotDelegate::CreateUObject(
                                                  this, &UMDGameInstance::HandleAsyncSave));
        return true;
    }
    return false;
}

void UMDGameInstance::ResetSaveGame()
{
    // Call handle function with no loaded save, this will reset the data
    HandleSaveGameLoaded(nullptr);
}

UObject* UMDGameInstance::GetPrimaryAssetIdObject(FPrimaryAssetId AssetId)
{
    UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
    {
        UE_LOG(LogTemp, Error, TEXT("MedurvalAssetManager not available to get primary asset: %s!"),
               *AssetId.ToString());
        return nullptr;
    }

    return AssetManager->GetPrimaryAssetObject(AssetId);
}

void UMDGameInstance::LoadObject(TSoftObjectPtr<> ObjectToLoad, FStreamableDelegate DelegateToCall)
{
    FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
    StreamableManager.RequestAsyncLoad(ObjectToLoad.ToSoftObjectPath(), DelegateToCall);
}

void UMDGameInstance::LoadClass(TSoftClassPtr<> ClassToLoad, FStreamableDelegate DelegateToCall)
{
    FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
    StreamableManager.RequestAsyncLoad(ClassToLoad.ToSoftObjectPath(), DelegateToCall);
}

void UMDGameInstance::LoadPrimaryAssetId(FPrimaryAssetId AssetId, FStreamableDelegate DelegateToCall,
                                         TArray<FName> BundlesToLoad)
{
    UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
    {
        UE_LOG(LogTemp, Error, TEXT("MedurvalAssetManager not available to load primary asset: %s!"),
               *AssetId.ToString());
        return;
    }

    AssetManager->LoadPrimaryAsset(AssetId, BundlesToLoad, DelegateToCall);
}

void UMDGameInstance::Init()
{
    Super::Init();
}

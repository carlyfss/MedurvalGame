// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Core/Actors/MDActor.h"

#include "Constants/CBConstants.h"
#include "Core/MDPlayerController.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMDActor::AMDActor()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.TickInterval = FCBConstants::TickInterval;

    USceneComponent *SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
    RootComponent = SceneComponent;
}

UMDGameInstance *AMDActor::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

AMDPlayerController *AMDActor::GetMDPlayerController() const
{
    return Cast<AMDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

UMedurvalAssetManager *AMDActor::GetMedurvalAssetManager() const
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
    {
        UE_LOG(LogTemp, Error, TEXT("MedurvalAssetManager not available!"));
        return nullptr;
    }

    return AssetManager;
}

void AMDActor::LoadObject(TSoftObjectPtr<> ObjectToLoad, FStreamableDelegate DelegateToCall)
{
    FStreamableManager &StreamableManager = UAssetManager::GetStreamableManager();
    StreamableManager.RequestAsyncLoad(ObjectToLoad.ToSoftObjectPath(), DelegateToCall);
}

void AMDActor::LoadClass(TSoftClassPtr<> ClassToLoad, FStreamableDelegate DelegateToCall)
{
    FStreamableManager &StreamableManager = UAssetManager::GetStreamableManager();
    StreamableManager.RequestAsyncLoad(ClassToLoad.ToSoftObjectPath(), DelegateToCall);
}

void AMDActor::LoadPrimaryAssetId(FPrimaryAssetId AssetId, FStreamableDelegate DelegateToCall, TArray<FName> BundlesToLoad)
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
    {
        UE_LOG(LogTemp, Error, TEXT("MedurvalAssetManager not available to load primary asset: %s!"), *AssetId.ToString());
        return;
    }

    AssetManager->LoadPrimaryAsset(AssetId, BundlesToLoad, DelegateToCall);
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDGameInstance.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Components/Base/MDEconomyComponent.h"
#include "Kismet/GameplayStatics.h"

UMDGameInstance::UMDGameInstance()
{
    
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

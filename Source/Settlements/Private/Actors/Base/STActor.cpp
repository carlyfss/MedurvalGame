// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Base/STActor.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMDGameInstance * ASTActor::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void ASTActor::LoadObject(TSoftObjectPtr<UObject> ObjectToLoad, FStreamableDelegate DelegateToCall)
{
    FStreamableManager &StreamableManager = UMedurvalAssetManager::GetStreamableManager();

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);
    StreamableManager.RequestAsyncLoad(ObjectToLoad.ToSoftObjectPath(), DelegateToCall);
}

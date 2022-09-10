// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/Actor.h"
#include "MDActor.generated.h"

class UMedurvalAssetManager;
class AMDPlayerController;
class UMDGameInstance;

UCLASS()
class MEDURVAL_API AMDActor : public AActor
{
    GENERATED_BODY()

public:
    AMDActor();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
    UMDGameInstance *GetMDGameInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
    AMDPlayerController *GetMDPlayerController() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
    UMedurvalAssetManager *GetMedurvalAssetManager() const;

    static void LoadObject(TSoftObjectPtr<UObject> ObjectToLoad, FStreamableDelegate DelegateToCall = FStreamableDelegate());

    static void LoadPrimaryAssetId(FPrimaryAssetId AssetId, FStreamableDelegate DelegateToCall = FStreamableDelegate(), TArray<FName> BundlesToLoad = TArray<FName>());
};

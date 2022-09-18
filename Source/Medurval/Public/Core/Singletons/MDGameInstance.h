// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MDGameInstance.generated.h"

class UMedurvalAssetManager;
class UMDEconomyComponent;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDGameInstance final : public UGameInstance
{
	GENERATED_BODY()
    
public:
    UMDGameInstance();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
	UMedurvalAssetManager* GetMedurvalAssetManager() const;

	static void LoadObject(TSoftObjectPtr<> ObjectToLoad, FStreamableDelegate DelegateToCall = FStreamableDelegate());

	static void LoadClass(TSoftClassPtr<> ClassToLoad, FStreamableDelegate DelegateToCall = FStreamableDelegate());

	static void LoadPrimaryAssetId(FPrimaryAssetId AssetId, FStreamableDelegate DelegateToCall = FStreamableDelegate(),
	                               TArray<FName> BundlesToLoad = TArray<FName>());

    virtual void Init() override;
};

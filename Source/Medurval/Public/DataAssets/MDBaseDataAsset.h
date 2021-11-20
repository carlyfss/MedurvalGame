// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "MDBaseDataAsset.generated.h"

UCLASS()
class MEDURVAL_API UMDBaseDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	UObject* Object;

	UPROPERTY(Transient)
	FSoftObjectPath ObjectSoftPath;
	
protected:

	UFUNCTION(BlueprintCallable, Category="Base Asset|Getters")
	UObject* GetAssetObject() const;
	
#pragma region ASYNC_LOAD_FUNCTIONS
	
	UFUNCTION(BlueprintCallable, Category="Base Asset|Async Load")
	void OnAssetLoaded();

	UFUNCTION(BlueprintCallable, Category="Base Asset|Async Load")
	void RequestAsyncLoadObject(const UObject* ObjectOwner);

	UFUNCTION(BlueprintCallable, Category="Base Asset|Async Load")
	void UnloadObject(const UObject* ObjectOwner);
	
#pragma endregion ASYNC_LOAD_FUNCTIONS
	
public:
	
	UPROPERTY(EditAnywhere, Category="Parts")
	TSoftClassPtr<UObject> AssetSoftClassRef;
};

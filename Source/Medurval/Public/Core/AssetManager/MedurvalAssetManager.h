// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MedurvalAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMedurvalAssetManager final : public UAssetManager
{
	GENERATED_BODY()

	UMedurvalAssetManager() {};

	virtual void StartInitialLoading() override;

	static const FPrimaryAssetType DefaultItemType;
	static const FPrimaryAssetType ConsumableItemType;

	

public:
	// Return the asset manager singleton class
	static UMedurvalAssetManager& Get();

	inline static const FName WorldBundle = "World";
	inline static const FName UIBundle = "UI";
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MedurvalAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class UMedurvalAssetManager : public UAssetManager
{
	GENERATED_BODY()

	UMedurvalAssetManager() {};

	virtual void StartInitialLoading() override;

	static const FPrimaryAssetType InventoryItemType;
	static const FPrimaryAssetType ConsumableItemType;

	// Return the asset manager singleton class
	static UMedurvalAssetManager& Get();
};

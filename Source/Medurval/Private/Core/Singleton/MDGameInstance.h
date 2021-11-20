// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UMDGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	FStreamableManager AssetLoader;
};

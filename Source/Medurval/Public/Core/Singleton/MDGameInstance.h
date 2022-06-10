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
class MEDURVAL_API UMDGameInstance final : public UGameInstance
{
	GENERATED_BODY()

public:

	FStreamableManager AssetLoader;
};

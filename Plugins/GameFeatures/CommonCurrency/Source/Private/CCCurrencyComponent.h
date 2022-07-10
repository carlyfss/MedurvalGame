// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/CBActorComponent.h"
#include "CCCurrencyComponent.generated.h"

/**
 * 
 */
UCLASS()
class UCCCurrencyComponent : public UCBActorComponent
{
    GENERATED_BODY()

    uint32 CurrentGoldCoins = 0;

    uint32 MaxGoldCoins = 100000;
};

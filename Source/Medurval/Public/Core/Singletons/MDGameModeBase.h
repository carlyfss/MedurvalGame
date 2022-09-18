// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MDGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API AMDGameModeBase final : public AGameModeBase
{
    GENERATED_BODY()

public:
    AMDGameModeBase();
    virtual ~AMDGameModeBase() = default;

    /** Called before begin play */
    virtual void StartPlay() override;
};

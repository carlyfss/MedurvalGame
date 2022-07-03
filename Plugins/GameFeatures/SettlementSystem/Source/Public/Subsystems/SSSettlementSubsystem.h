// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SSSettlementSubsystem.generated.h"

/**
 *
 */
UCLASS(DisplayName = "SettlementSubsystem")
class SETTLEMENTSYSTEM_API USSSettlementSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Actors/MDActor.h"
#include "Subsystems/STSettlementSubsystem.h"
#include "STActor.generated.h"

/**
 * 
 */
UCLASS()
class ASTActor : public AMDActor
{
	GENERATED_BODY()

public:
    USTSettlementSubsystem *GetSettlementSubsystem() const;
};

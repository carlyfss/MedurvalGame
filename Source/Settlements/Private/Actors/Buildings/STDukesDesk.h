// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/STBuildingActor.h"
#include "Components/STSettlementComponent.h"
#include "STDukesDesk.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="DukesDesk"))
class ASTDukesDesk : public ASTBuildingActor
{
    GENERATED_BODY()

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTSettlementComponent> SettlementComponent = nullptr;

public:
    ASTDukesDesk();
};

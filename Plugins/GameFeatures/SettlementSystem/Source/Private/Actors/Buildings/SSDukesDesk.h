// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBActor.h"
#include "Actors/SSBuildingActor.h"
#include "SSDukesDesk.generated.h"

class USSSettlementComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="DukesDesk"))
class ASSDukesDesk : public ASSBuildingActor
{
    GENERATED_BODY()

    ASSDukesDesk();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="DukesDesk", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementComponent> SettlementComponent;
};

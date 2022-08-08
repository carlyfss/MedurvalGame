// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBActor.h"
#include "SSActor.generated.h"

class UMDGameInstance;
/**
 * 
 */
UCLASS()
class ASSActor : public ACBActor
{
	GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="SSActor")
    UMDGameInstance* GetMDGameInstance() const;
};

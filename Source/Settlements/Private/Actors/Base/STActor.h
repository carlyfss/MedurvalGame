// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBActor.h"
#include "Engine/StreamableManager.h"
#include "STActor.generated.h"

class UMDGameInstance;
/**
 * 
 */
UCLASS()
class ASTActor : public ACBActor
{
	GENERATED_BODY()

protected:
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="SSActor")
    UMDGameInstance* GetMDGameInstance() const;

public:
    static void LoadObject(TSoftObjectPtr<UObject> ObjectToLoad, FStreamableDelegate DelegateToCall = FStreamableDelegate());
};

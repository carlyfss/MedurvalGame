// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MDActorComponent.generated.h"

class AMDPlayerController;
class UMDGameInstance;
class UMDEconomyComponent;

UCLASS(Blueprintable, BlueprintType)
class MEDURVAL_API UMDActorComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UMDActorComponent();

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
    UMDGameInstance* GetMDGameInstance() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="MDActor")
    AMDPlayerController* GetMDPlayerController() const;
};

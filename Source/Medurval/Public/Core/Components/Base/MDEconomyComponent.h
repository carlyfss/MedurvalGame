// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "Core/Structs/MDCurrency.h"
#include "MDEconomyComponent.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDEconomyComponent : public UMDActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEconomyComponent", meta=(AllowPrivateAccess=true))
    FMDCurrency Configuration;

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="MDEconomyComponent")
    int AddAmount(int &CurrentAmount, int Amount);

    UFUNCTION(BlueprintCallable, Category="MDEconomyComponent")
    int RemoveAmount(int &CurrentAmount, int Amount);

    UFUNCTION(BlueprintCallable, Category="MDEconomyComponent")
    void SetCurrencyIcon(TSoftObjectPtr<UImage> NewIcon);

    FMDCurrency GetConfiguration() const;
};

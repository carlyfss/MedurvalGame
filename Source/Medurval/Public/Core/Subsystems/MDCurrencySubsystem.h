// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Structs/MDCurrency.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MDCurrencySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDCurrencySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CurrencyComponent", meta=(AllowPrivateAccess=true))
    FMDCurrency Configuration;

public:
    UFUNCTION(BlueprintCallable, Category="CurrencyComponent")
    int AddAmount(int &CurrentAmount, int Amount);

    UFUNCTION(BlueprintCallable, Category="CurrencyComponent")
    int RemoveAmount(int &CurrentAmount, int Amount);

    UFUNCTION(BlueprintCallable, Category="CurrencyComponent")
    void SetCurrencyIcon(TSoftObjectPtr<UImage> NewIcon);

    FMDCurrency GetConfiguration() const;
};

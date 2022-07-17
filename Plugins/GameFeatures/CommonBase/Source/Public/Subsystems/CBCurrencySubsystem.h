// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Structs/CBCurrency.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CBCurrencySubsystem.generated.h"

/**
 * 
 */
UCLASS()
class COMMONBASE_API UCBCurrencySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CurrencyComponent", meta=(AllowPrivateAccess=true))
    FCBCurrency Configuration;

public:
    UFUNCTION(BlueprintCallable, Category="CurrencyComponent")
    int AddAmount(int &CurrentAmount, int Amount);

    UFUNCTION(BlueprintCallable, Category="CurrencyComponent")
    int RemoveAmount(int &CurrentAmount, int Amount);

    UFUNCTION(BlueprintCallable, Category="CurrencyComponent")
    void SetCurrencyIcon(TSoftObjectPtr<UImage> NewIcon);

    FCBCurrency GetConfiguration() const;
};

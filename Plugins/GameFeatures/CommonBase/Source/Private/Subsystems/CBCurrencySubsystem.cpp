// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Subsystems/CBCurrencySubsystem.h"

void UCBCurrencySubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    Configuration = FCBCurrency(FName("Gold"));
}

void UCBCurrencySubsystem::Deinitialize()
{
    Super::Deinitialize();

    // Save current configuration
}

int UCBCurrencySubsystem::AddAmount(int &CurrentAmount, int Amount)
{
    const int AmountSum = CurrentAmount + Amount;
    CurrentAmount = FMath::Clamp(AmountSum, Configuration.MinAmount, Configuration.MaxAmount);
    return CurrentAmount;
}

int UCBCurrencySubsystem::RemoveAmount(int &CurrentAmount, int Amount)
{
    const int AmountSum = CurrentAmount - Amount;
    CurrentAmount = FMath::Clamp(AmountSum, Configuration.MinAmount, Configuration.MaxAmount);
    return CurrentAmount;
}

void UCBCurrencySubsystem::SetCurrencyIcon(TSoftObjectPtr<UImage> NewIcon)
{
    Configuration.Icon = NewIcon;
}

FCBCurrency UCBCurrencySubsystem::GetConfiguration() const
{
    return Configuration;
}

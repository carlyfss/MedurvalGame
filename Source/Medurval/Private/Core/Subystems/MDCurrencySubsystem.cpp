// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Subsystems/MDCurrencySubsystem.h"

void UMDCurrencySubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    Super::Initialize(Collection);

    Configuration = FMDCurrency(FName("Gold"));
}

void UMDCurrencySubsystem::Deinitialize()
{
    Super::Deinitialize();

    // Save current configuration
}

int UMDCurrencySubsystem::AddAmount(int &CurrentAmount, int Amount)
{
    const int AmountSum = CurrentAmount + Amount;
    CurrentAmount = FMath::Clamp(AmountSum, Configuration.MinAmount, Configuration.MaxAmount);
    return CurrentAmount;
}

int UMDCurrencySubsystem::RemoveAmount(int &CurrentAmount, int Amount)
{
    const int AmountSum = CurrentAmount - Amount;
    CurrentAmount = FMath::Clamp(AmountSum, Configuration.MinAmount, Configuration.MaxAmount);
    return CurrentAmount;
}

void UMDCurrencySubsystem::SetCurrencyIcon(TSoftObjectPtr<UImage> NewIcon)
{
    Configuration.Icon = NewIcon;
}

FMDCurrency UMDCurrencySubsystem::GetConfiguration() const
{
    return Configuration;
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/Base/MDEconomyComponent.h"

void UMDEconomyComponent::BeginPlay()
{
    Super::BeginPlay();

    Configuration = FMDCurrency(FName("Gold"));
}

int UMDEconomyComponent::AddAmount(int &CurrentAmount, int Amount)
{
    const int AmountSum = CurrentAmount + Amount;
    CurrentAmount = FMath::Clamp(AmountSum, Configuration.MinAmount, Configuration.MaxAmount);
    return CurrentAmount;
}

int UMDEconomyComponent::RemoveAmount(int &CurrentAmount, int Amount)
{
    const int AmountSum = CurrentAmount - Amount;
    CurrentAmount = FMath::Clamp(AmountSum, Configuration.MinAmount, Configuration.MaxAmount);
    return CurrentAmount;
}

void UMDEconomyComponent::SetCurrencyIcon(TSoftObjectPtr<UImage> NewIcon)
{
    Configuration.Icon = NewIcon;
}

FMDCurrency UMDEconomyComponent::GetConfiguration() const
{
    return Configuration;
}



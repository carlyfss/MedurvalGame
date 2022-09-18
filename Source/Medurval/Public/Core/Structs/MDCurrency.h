// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Components/Image.h"
#include "MDCurrency.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "CommonCurrency"))
struct MEDURVAL_API FMDCurrency
{
    GENERATED_BODY()

    FORCEINLINE FMDCurrency();

    FORCEINLINE FMDCurrency(FName CurrencyName);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    FName Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    int MinAmount = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    int MaxAmount = 999999999;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<UImage> Icon;
};

inline FMDCurrency::FMDCurrency()
{
}

inline FMDCurrency::FMDCurrency(FName CurrencyName)
{
    Name = CurrencyName;
}

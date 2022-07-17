// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once
#include "Components/Image.h"
#include "CBCurrency.generated.h"

USTRUCT(BlueprintType, meta = (DisplayName = "CommonCurrency"))
struct COMMONBASE_API FCBCurrency
{
    GENERATED_BODY()

    FORCEINLINE FCBCurrency();

    FORCEINLINE FCBCurrency(FName CurrencyName);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    FName Name;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    int MinAmount = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    int MaxAmount = 999999999;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="CommonCurrency", meta=(AllowPrivateAccess=true))
    TSoftObjectPtr<UImage> Icon;
};

inline FCBCurrency::FCBCurrency()
{
}

inline FCBCurrency::FCBCurrency(FName CurrencyName)
{
    Name = CurrencyName;
}

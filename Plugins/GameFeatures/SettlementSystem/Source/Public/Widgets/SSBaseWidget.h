// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "SSBaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSBaseWidget : public UCommonUserWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="BaseWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<ACharacter> PlayerReference = nullptr;

public:
    UFUNCTION(BlueprintCallable, Category="BaseWidget")
    void SetWidgetVisibility(bool bIsVisible);
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonButtonBase.h"
#include "CommonTextBlock.h"
#include "MDButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDButtonWidget : public UCommonButtonBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="MDButtonWidget", meta=(AllowPrivateAccess=true))
	FText ButtonText;

	UPROPERTY(BlueprintReadOnly, Category="MDButtonWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UCommonTextBlock> ButtonTextBlock;

public:
	UFUNCTION(BlueprintCallable, Category="MDButtonWidget")
	void SetButtonText(FText Text);
};

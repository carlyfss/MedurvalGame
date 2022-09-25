// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDActivatableWidget.h"
#include "MDActivatableWidgetStack.h"
#include "MDGameBaseWidget.generated.h"

class UMedurvalAssetManager;
class AMDPlayerController;
class UMDGameInstance;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDGameBaseWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="MDGameBaseWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UMDActivatableWidgetStack> GameStack;

	UPROPERTY(BlueprintReadOnly, Category="MDGameBaseWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UMDActivatableWidgetStack> PromptStack;

public:
	UFUNCTION(BlueprintCallable, Category="MDGameBaseWidget")
	UMDActivatableWidget* PushWidget(TSubclassOf<UMDActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category="MDGameBaseWidget")
	UMDActivatableWidget* PushPrompt(TSubclassOf<UMDActivatableWidget> WidgetClass);
};

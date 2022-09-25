// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Widgets/MDGameBaseWidget.h"

UMDActivatableWidget* UMDGameBaseWidget::PushWidget(TSubclassOf<UMDActivatableWidget> WidgetClass)
{
	return Cast<UMDActivatableWidget>(GameStack->AddWidget(WidgetClass));
}

UMDActivatableWidget* UMDGameBaseWidget::PushPrompt(TSubclassOf<UMDActivatableWidget> WidgetClass)
{
	return Cast<UMDActivatableWidget>(PromptStack->AddWidget(WidgetClass));
}

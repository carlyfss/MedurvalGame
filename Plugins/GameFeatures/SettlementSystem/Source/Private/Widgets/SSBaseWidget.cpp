// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSBaseWidget.h"

void USSBaseWidget::SetWidgetVisibility(bool bIsVisible)
{
    if (bIsVisible)
    {
        SetVisibility(ESlateVisibility::Visible);
        return;
    }

    SetVisibility(ESlateVisibility::Collapsed);
}

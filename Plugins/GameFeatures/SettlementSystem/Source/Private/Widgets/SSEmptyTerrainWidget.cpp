// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSEmptyTerrainWidget.h"

void USSEmptyTerrainWidget::SetWidgetVisibility(bool bIsVisible)
{
    if (bIsVisible)
    {
        SetVisibility(ESlateVisibility::Visible);
        return;
    }

    SetVisibility(ESlateVisibility::Collapsed);
}

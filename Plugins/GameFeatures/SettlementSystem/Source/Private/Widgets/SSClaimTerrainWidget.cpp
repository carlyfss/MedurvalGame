// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSClaimTerrainWidget.h"

void USSClaimTerrainWidget::SetWidgetVisibility(bool bIsVisible)
{
    if (bIsVisible)
    {
        SetVisibility(ESlateVisibility::Visible);
        return;
    }

    SetVisibility(ESlateVisibility::Collapsed);
}

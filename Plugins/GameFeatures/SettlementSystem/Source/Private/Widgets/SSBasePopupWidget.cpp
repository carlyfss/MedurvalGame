// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSBasePopupWidget.h"

void USSBasePopupWidget::UpdateWidgetInfo_Implementation(ASSTerrainActor *TerrainActor)
{
}

void USSBasePopupWidget::UpdateWidget_Implementation()
{
}

void USSBasePopupWidget::StartUpdatingPosition_Implementation()
{
}

void USSBasePopupWidget::StopUpdatingPosition_Implementation()
{
}

void USSBasePopupWidget::ShowPopupWidget()
{
    SetVisibility(ESlateVisibility::Visible);
}

void USSBasePopupWidget::SetWidgetVisibility(bool bIsVisible)
{
    const FTimerDelegate ShowTimerDelegate = FTimerDelegate::CreateUObject(this, &USSBasePopupWidget::ShowPopupWidget);

    if (!bIsVisible)
    {
        StopUpdatingPosition();
        SetVisibility(ESlateVisibility::Hidden);
        return;
    }
    
    StartUpdatingPosition();
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, ShowTimerDelegate, ShowPopupDelay, false);
        
}

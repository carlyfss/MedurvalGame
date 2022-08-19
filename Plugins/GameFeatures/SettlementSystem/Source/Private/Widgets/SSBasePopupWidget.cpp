// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSBasePopupWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Core/MDPlayerController.h"
#include "Kismet/GameplayStatics.h"

void USSBasePopupWidget::UpdateWidgetInfo_Implementation(ASSTerrainActor *TerrainActor)
{
}

void USSBasePopupWidget::UpdateWidget()
{
    FVector2D WidgetPosition;
    UGameplayStatics::ProjectWorldToScreen(GetMDPlayerController(), TerrainLocation, WidgetPosition, true);

    const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
    const FVector2D HalvedViewportSize = ViewportSize / 2;
    const FVector2D NewWidgetPosition = WidgetPosition - HalvedViewportSize + WidgetPositionOffset;

    const FWidgetTransform WidgetTransform = FWidgetTransform(NewWidgetPosition, FVector2D(1,1), FVector2D(0,0), 0.f);
    SetRenderTransform(WidgetTransform);
}

void USSBasePopupWidget::StartUpdatingPosition()
{
    const FTimerDelegate UpdateDelegate = FTimerDelegate::CreateUObject(this, &USSBasePopupWidget::UpdateWidget);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, UpdateDelegate, UpdateWidgetInterval, true, 0.f);
}

void USSBasePopupWidget::StopUpdatingPosition()
{
    if (!TimerHandle.IsValid())
        return;

    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
    TimerHandle.Invalidate();
}

void USSBasePopupWidget::NativeOnActivated()
{
    Super::NativeOnActivated();

    FTimerHandle SetVisibilityTimerHandle;
    const FTimerDelegate SetVisibilityDelegate = FTimerDelegate::CreateUObject(this, &USSBasePopupWidget::SetVisibility, ESlateVisibility::Visible);
    GetWorld()->GetTimerManager().SetTimer(SetVisibilityTimerHandle, SetVisibilityDelegate, UpdateWidgetInterval, false, 0.05f);
    
    StartUpdatingPosition();
}

void USSBasePopupWidget::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    FTimerHandle SetVisibilityTimerHandle;
    const FTimerDelegate SetVisibilityDelegate = FTimerDelegate::CreateUObject(this, &USSBasePopupWidget::SetVisibility, ESlateVisibility::Collapsed);
    GetWorld()->GetTimerManager().SetTimer(SetVisibilityTimerHandle, SetVisibilityDelegate, UpdateWidgetInterval, false, 0.f);

    StopUpdatingPosition();
}

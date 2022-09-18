// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/STBasePopupWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Actors/STTerrainActor.h"
#include "Core/Singletons/MDPlayerController.h"
#include "Kismet/GameplayStatics.h"

void USTBasePopupWidget::UpdateWidgetInfo_Implementation(ASTTerrainActor *TerrainActor)
{
}

void USTBasePopupWidget::UpdateWidget()
{
    FVector2D WidgetPosition;
    UGameplayStatics::ProjectWorldToScreen(GetMDPlayerController(), TerrainLocation, WidgetPosition, true);

    const FVector2D ViewportSize = UWidgetLayoutLibrary::GetViewportSize(GetWorld());
    const FVector2D HalvedViewportSize = ViewportSize / 2;
    const FVector2D NewWidgetPosition = WidgetPosition - HalvedViewportSize + WidgetPositionOffset;

    const FWidgetTransform WidgetTransform = FWidgetTransform(NewWidgetPosition, FVector2D(1,1), FVector2D(0,0), 0.f);
    SetRenderTransform(WidgetTransform);
}

void USTBasePopupWidget::StartUpdatingPosition()
{
    const FTimerDelegate UpdateDelegate = FTimerDelegate::CreateUObject(this, &USTBasePopupWidget::UpdateWidget);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, UpdateDelegate, UpdateWidgetInterval, true, 0.f);
}

void USTBasePopupWidget::StopUpdatingPosition()
{
    if (!TimerHandle.IsValid())
        return;

    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
    TimerHandle.Invalidate();
}

void USTBasePopupWidget::NativeOnActivated()
{
    Super::NativeOnActivated();

    FTimerHandle SetVisibilityTimerHandle;
    const FTimerDelegate SetVisibilityDelegate = FTimerDelegate::CreateUObject(this, &USTBasePopupWidget::SetVisibility, ESlateVisibility::Visible);
    GetWorld()->GetTimerManager().SetTimer(SetVisibilityTimerHandle, SetVisibilityDelegate, UpdateWidgetInterval, false, 0.05f);
    
    StartUpdatingPosition();
}

void USTBasePopupWidget::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();

    FTimerHandle SetVisibilityTimerHandle;
    const FTimerDelegate SetVisibilityDelegate = FTimerDelegate::CreateUObject(this, &USTBasePopupWidget::SetVisibility, ESlateVisibility::Collapsed);
    GetWorld()->GetTimerManager().SetTimer(SetVisibilityTimerHandle, SetVisibilityDelegate, UpdateWidgetInterval, false, 0.f);

    StopUpdatingPosition();
}

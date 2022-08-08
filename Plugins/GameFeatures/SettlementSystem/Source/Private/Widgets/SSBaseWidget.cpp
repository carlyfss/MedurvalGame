// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSBaseWidget.h"

#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USSBaseWidget::InitializeWidget_Implementation()
{
    InitializeWidget();
}

UMDGameInstance * USSBaseWidget::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void USSBaseWidget::SetWidgetVisibility(bool bIsVisible)
{
    if (bIsVisible)
    {
        SetVisibility(ESlateVisibility::Visible);
        return;
    }

    SetVisibility(ESlateVisibility::Collapsed);
}

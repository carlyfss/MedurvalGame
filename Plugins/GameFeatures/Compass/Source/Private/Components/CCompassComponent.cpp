// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Components/CCompassComponent.h"

#include "Structs/FCDirectionInfo.h"
#include "Subsystems/CCompassSubsystem.h"
#include "UI/CCompassWidget.h"

UCCompassComponent::UCCompassComponent()
{
    const FCDirectionInfo *NorthDirection = new FCDirectionInfo(FText::FromName("N"), 0);
    const FCDirectionInfo *EastDirection = new FCDirectionInfo(FText::FromName("E"), 90);
    const FCDirectionInfo *SouthDirection = new FCDirectionInfo(FText::FromName("S"), 180);
    const FCDirectionInfo *WestDirection = new FCDirectionInfo(FText::FromName("W"), -90);

    Directions.Add(*NorthDirection);
    Directions.Add(*EastDirection);
    Directions.Add(*SouthDirection);
    Directions.Add(*WestDirection);
}

void UCCompassComponent::SetCompassWidget(UCCompassWidget *WidgetReference)
{
    CompassWidget = WidgetReference;
}

UCCompassWidget *UCCompassComponent::GetCompassWidget() const
{
    return CompassWidget;
}

TArray<FCDirectionInfo> UCCompassComponent::GetDirections() const
{
    return Directions;
}

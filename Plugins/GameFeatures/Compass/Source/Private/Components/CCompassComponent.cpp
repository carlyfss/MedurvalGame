// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Components/CCompassComponent.h"

#include "UI/CCompassWidget.h"

void UCCompassComponent::SetCompassWidget(UCCompassWidget *WidgetReference)
{
    CompassWidget = WidgetReference;
}

UCCompassWidget *UCCompassComponent::GetCompassWidget() const
{
    return CompassWidget;
}

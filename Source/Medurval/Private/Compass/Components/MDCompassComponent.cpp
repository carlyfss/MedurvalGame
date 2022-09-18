// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Compass/Components/MDCompassComponent.h"

#include "Compass/Widgets/MDCompassWidget.h"

void UMDCompassComponent::SetCompassWidget(UMDCompassWidget* WidgetReference)
{
	CompassWidget = WidgetReference;
}

UMDCompassWidget* UMDCompassComponent::GetCompassWidget() const
{
	return CompassWidget;
}

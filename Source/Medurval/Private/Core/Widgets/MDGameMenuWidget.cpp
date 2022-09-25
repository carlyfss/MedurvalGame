// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Widgets/MDGameMenuWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Core/Singletons/MDPlayerController.h"

void UMDGameMenuWidget::InitializeHeaderButtons()
{
	InventoryButton->SetButtonText(InventoryButtonText);
	InventoryButton->SetIsSelectable(true);

	FactionButton->SetButtonText(FactionButtonText);
	FactionButton->SetIsSelectable(true);

	WorldMapButton->SetButtonText(WorldMapButtonText);
	WorldMapButton->SetIsSelectable(true);

	SettingsButton->SetButtonText(SettingsButtonText);
	SettingsButton->SetIsSelectable(true);
}

UMDActivatableWidget* UMDGameMenuWidget::CreateAndAddWidgetToSwitcher(TSubclassOf<UMDActivatableWidget> WidgetClass)
{
	UUserWidget* WidgetCreated = UWidgetBlueprintLibrary::Create(GetWorld(), WidgetClass, GetMDPlayerController());

	if (WidgetCreated)
	{
		WidgetSwitcher->AddChild(WidgetCreated);
	}

	return Cast<UMDActivatableWidget>(WidgetCreated);
}

void UMDGameMenuWidget::ClearHeaderButtonsSelection()
{
	InventoryButton->ClearSelection();
	FactionButton->ClearSelection();
	WorldMapButton->ClearSelection();
	SettingsButton->ClearSelection();
}

void UMDGameMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeHeaderButtons();

	SetupInventoryWidget();
	SetupFactionWidget();
	SetupSettingsWidget();
	SetupWorldMapWidget();

	InventoryButton->SetIsSelected(true);
}

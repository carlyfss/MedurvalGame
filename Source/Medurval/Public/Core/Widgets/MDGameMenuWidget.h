// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDActivatableWidget.h"
#include "MDButtonWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Inventory/Components/MDInventoryComponent.h"
#include "MDGameMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDGameMenuWidget : public UMDActivatableWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="MDGameMenuWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UWidgetSwitcher> WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, Category="MDGameMenuWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UMDButtonWidget> InventoryButton;

	UPROPERTY(BlueprintReadOnly, Category="MDGameMenuWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UMDButtonWidget> FactionButton;

	UPROPERTY(BlueprintReadOnly, Category="MDGameMenuWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UMDButtonWidget> WorldMapButton;

	UPROPERTY(BlueprintReadOnly, Category="MDGameMenuWidget", meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UMDButtonWidget> SettingsButton;

	FText InventoryButtonText = FText::FromString("Inventory");
	FText FactionButtonText = FText::FromString("Faction");
	FText WorldMapButtonText = FText::FromString("World Map");
	FText SettingsButtonText = FText::FromString("Settings");

protected:
	void InitializeHeaderButtons();

	UFUNCTION(BlueprintCallable, Category="MDGameMenuWidget")
	UMDActivatableWidget* CreateAndAddWidgetToSwitcher(TSubclassOf<UMDActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category="MDGameMenuWidget")
	void ClearHeaderButtonsSelection();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDGameMenuWidget")
	void SetupInventoryWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDGameMenuWidget")
	void SetupFactionWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDGameMenuWidget")
	void SetupWorldMapWidget();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDGameMenuWidget")
	void SetupSettingsWidget();

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDGameMenuWidget")
	void ConfigureInventoryWidget(UMDInventoryComponent* InventoryComponent);

	virtual void NativeConstruct() override;
};

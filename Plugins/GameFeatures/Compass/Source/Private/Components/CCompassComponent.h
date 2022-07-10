// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/CBActorComponent.h"
#include "CCompassComponent.generated.h"

struct FCDirectionInfo;
class UUserWidget;
class UCCompassWidget;

/** * */
UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "CompassComponent"))
class UCCompassComponent : public UCBActorComponent
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Compass|Configuration", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> CompassWidgetClass = nullptr;

    UPROPERTY(BlueprintSetter = SetCompassWidget, BlueprintGetter = GetCompassWidget, Category = "Compass|Configuration")
    TObjectPtr<UCCompassWidget> CompassWidget = nullptr;

protected:
    UFUNCTION(BlueprintCallable, Category = "Compass|Configuration")
    void SetCompassWidget(UCCompassWidget *WidgetReference);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Category|Configuration")
    UCCompassWidget *GetCompassWidget() const;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Compass|Configuration")
    void UpdateDirectionWidgets();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Compass|Configuration")
    void UpdateMarkersWidgets();
};

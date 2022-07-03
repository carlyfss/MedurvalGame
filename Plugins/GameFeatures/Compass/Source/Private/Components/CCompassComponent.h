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

    UCCompassComponent();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Compass|Configuration", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> CompassWidgetClass = nullptr;

    UPROPERTY(BlueprintSetter = SetCompassWidget, BlueprintGetter = GetCompassWidget, Category = "Compass|Configuration")
    TObjectPtr<UCCompassWidget> CompassWidget = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintGetter=GetDirections, Category="Compass|Configuration", meta = (AllowPrivateAccess = true))
    TArray<FCDirectionInfo> Directions;

protected:
    UFUNCTION(BlueprintCallable, Category = "Compass|Configuration")
    void SetCompassWidget(UCCompassWidget *WidgetReference);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Category|Configuration")
    UCCompassWidget *GetCompassWidget() const;

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Category|Configuration")
    TArray<FCDirectionInfo> GetDirections() const;
};

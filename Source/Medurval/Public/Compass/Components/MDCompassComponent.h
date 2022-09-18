// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "MDCompassComponent.generated.h"

struct FMDDirectionInfo;
class UUserWidget;
class UMDCompassWidget;

/** * */
UCLASS(BlueprintType, Blueprintable, meta = (DisplayName = "CompassComponent"))
class MEDURVAL_API UMDCompassComponent : public UMDActorComponent
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Compass|Configuration", meta = (AllowPrivateAccess = true))
    TSubclassOf<UUserWidget> CompassWidgetClass = nullptr;

    UPROPERTY(BlueprintSetter = SetCompassWidget, BlueprintGetter = GetCompassWidget, Category = "Compass|Configuration")
    TObjectPtr<UMDCompassWidget> CompassWidget = nullptr;

protected:
    UFUNCTION(BlueprintCallable, Category = "Compass|Configuration")
    void SetCompassWidget(UMDCompassWidget* WidgetReference);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Category|Configuration")
    UMDCompassWidget* GetCompassWidget() const;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Compass|Configuration")
    void UpdateDirectionWidgets();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="Compass|Configuration")
    void UpdateMarkersWidgets();
};

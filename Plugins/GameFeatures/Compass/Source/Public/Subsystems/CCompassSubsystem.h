// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Structs/FCDirectionInfo.h"
#include "Structs/FCMarkerInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CCompassSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateDirectionWidgets);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateMarkerWidgets);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddMarkerToCompass, FCMarkerInfo, TargetMarker);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSwitchVisibility);

class UCCompassWidget;
/**
 *
 */
UCLASS(DisplayName = "CompassSubsystem")
class COMPASS_API UCCompassSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

    FTimerHandle TimerHandle;

    float TimerInterval = 0.01f;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations")
    float MaxWidgetTranslation = 350;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FCDirectionInfo> Directions;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FCMarkerInfo> Markers;

    const int CircleDegrees = 360;

    const float UnitsPerMeter = 100.0f;

    void UpdateAllWidgets() const;

protected:
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateDirectionWidgets UpdateDirectionWidgets;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateMarkerWidgets OnUpdateMarkerWidgets;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnAddMarkerToCompass OnAddMarkerToCompass;

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnSwitchVisibility OnSwitchVisibility;

    UFUNCTION(BlueprintCallable, Category="Compass")
    void PauseUnpauseTimer(bool bIsToPause, bool bIsToUnpause);

public:
    UFUNCTION(BlueprintCallable, Category="Compass")
    float RotationToCircleDegrees(float In) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    float GetDeltaClockwise(float A, float B, bool bIsClockwise) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    FVector2D RotationsToTranslations(FRotator RotationA, FRotator RotationB, bool &bIsClockwise, bool &bIsInRadarSigth) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    TArray<FCDirectionInfo> GetDirections() const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    TArray<FCMarkerInfo> GetMarkers() const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    int UpdateMarkerDistance(FCMarkerInfo MarkerToCalculate) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    void AddMarkerToCompass(FCMarkerInfo Marker);
};

inline void UCCompassSubsystem::UpdateAllWidgets() const
{
    UpdateDirectionWidgets.Broadcast();

    if (Markers.Num() > 0)
    {
        OnUpdateMarkerWidgets.Broadcast();
    }
}

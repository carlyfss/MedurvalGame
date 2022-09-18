// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Compass/Structs/MDDirectionInfo.h"
#include "Compass/Structs/MDMarkerInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MDCompassSubsystem.generated.h"

class UMDCompassWidget;
/**
 *
 */
UCLASS(DisplayName = "CompassSubsystem")
class MEDURVAL_API UMDCompassSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

    FTimerHandle TimerHandle;

    float TimerInterval = 0.01f;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations")
    float MaxWidgetTranslation = 350;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FMDDirectionInfo> Directions;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FMDMarkerInfo> Markers;

    const int CircleDegrees = 360;

    const float UnitsPerMeter = 100.0f;

    void UpdateAllWidgets() const;

protected:
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateDirectionWidgets);
    
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateDirectionWidgets UpdateDirectionWidgets;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateMarkerWidgets);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateMarkerWidgets OnUpdateMarkerWidgets;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddMarkerToCompass, FMDMarkerInfo, TargetMarker);

    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnAddMarkerToCompass OnAddMarkerToCompass;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchVisibility, bool, bSetVisibility);
    
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnSwitchVisibility OnSwitchVisibility;

    UFUNCTION(BlueprintCallable, Category="Compass")
    void PauseUnpauseTimer(bool bIsToPause, bool bIsToUnpause);

    UFUNCTION(BlueprintCallable, Category="Compass")
    float RotationToCircleDegrees(float In) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    float GetDeltaClockwise(float A, float B, bool bIsClockwise) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    FVector2D RotationsToTranslations(FRotator RotationA, FRotator RotationB, bool &bIsClockwise, bool &bIsInRadarSigth) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    int UpdateMarkerDistance(FMDMarkerInfo MarkerToCalculate) const;

public:
    UFUNCTION(BlueprintCallable, Category="Compass")
    TArray<FMDDirectionInfo> GetDirections() const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    TArray<FMDMarkerInfo> GetMarkers() const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    void AddMarkerToCompass(FMDMarkerInfo Marker);
};

inline void UMDCompassSubsystem::UpdateAllWidgets() const
{
    UpdateDirectionWidgets.Broadcast();

    if (Markers.Num() > 0)
    {
        OnUpdateMarkerWidgets.Broadcast();
    }
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Structs/FCDirectionInfo.h"
#include "Structs/FCMarkerInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CCompassSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateDirectionWidgets);

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

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations")
    float TimerInterval = 0.025f;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations")
    float MaxWidgetTranslation = 350;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FCDirectionInfo> Directions;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FCMarkerInfo> Markers;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FCMarkerInfo> DefaultMarkers;

    const int CircleDegrees = 360;

    void UpdateAllWidgets() const;

protected:
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnUpdateDirectionWidgets UpdateDirectionWidgets;

public:
    UFUNCTION(BlueprintCallable, Category="Compass")
    float RotationToCircleDegrees(float In) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    float GetDeltaClockwise(float A, float B, bool bIsClockwise) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    FVector2D RotationsToTranslations(FRotator RotationA, FRotator RotationB, bool &bIsClockwise, bool &bIsInRadarSigth) const;

    UFUNCTION(BlueprintCallable, Category="Compass")
    void SetDirections(TArray<FCDirectionInfo> DirectionInfos);

    UFUNCTION(BlueprintCallable, Category="Compass")
    TArray<FCDirectionInfo> GetDirections();
};

inline void UCCompassSubsystem::UpdateAllWidgets() const
{
    UpdateDirectionWidgets.Broadcast();
}

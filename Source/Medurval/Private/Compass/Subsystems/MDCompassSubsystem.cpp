// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Compass/Subsystems/MDCompassSubsystem.h"
#include "GameFramework/Character.h"

void UMDCompassSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    const FMDDirectionInfo* NorthDirection = new FMDDirectionInfo(FText::FromName("N"), 0);
    const FMDDirectionInfo* EastDirection = new FMDDirectionInfo(FText::FromName("E"), 90);
    const FMDDirectionInfo* SouthDirection = new FMDDirectionInfo(FText::FromName("S"), 180);
    const FMDDirectionInfo* WestDirection = new FMDDirectionInfo(FText::FromName("W"), -90);

    Directions.Add(*NorthDirection);
    Directions.Add(*EastDirection);
    Directions.Add(*SouthDirection);
    Directions.Add(*WestDirection);

    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &UMDCompassSubsystem::UpdateAllWidgets);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimerInterval, true);
}

void UMDCompassSubsystem::Deinitialize()
{
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

void UMDCompassSubsystem::PauseUnpauseTimer(bool bIsToPause, bool bIsToUnpause)
{
    if (GetWorld()->GetTimerManager().IsTimerPaused(TimerHandle) && bIsToUnpause)
    {
        GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
    }

    if (bIsToPause)
    {
        GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
    }
}

float UMDCompassSubsystem::RotationToCircleDegrees(float In) const
{
    float SelectedFloat = In;

    if (In < 0)
    {
        const int InIntValue = FMath::Floor(In);
        SelectedFloat = (CircleDegrees + InIntValue) % CircleDegrees;
    }

    return SelectedFloat;
}

float UMDCompassSubsystem::GetDeltaClockwise(float A, float B, bool bIsClockwise) const
{
    float AInput = fmod(A, CircleDegrees);
    float BInput = fmod(B, CircleDegrees);

    if (bIsClockwise)
    {
        if (AInput == BInput)
        {
            return 0;
        }

        if (AInput < BInput)
        {
            return BInput - AInput;
        }

        return CircleDegrees - (AInput - BInput);
    }

    if (AInput == BInput)
    {
        return 0;
    }

    if (AInput < BInput)
    {
        return CircleDegrees - (BInput - AInput);
    }

    return AInput - BInput;
}

FVector2D UMDCompassSubsystem::RotationsToTranslations(FRotator RotationA, FRotator RotationB, bool& bIsClockwise,
                                                       bool& bIsInRadarSigth) const
{
    constexpr float FloatValue = 90;
    const float RotationAInCircleDeg = RotationToCircleDegrees(RotationA.Yaw);
    const float RotationBInCircleDeg = RotationToCircleDegrees(RotationB.Yaw);

    const float ClockwiseRotationDistance = GetDeltaClockwise(RotationAInCircleDeg, RotationBInCircleDeg, true);
    const float AntiClockwiseRotationDistance = GetDeltaClockwise(RotationAInCircleDeg, RotationBInCircleDeg, false);

    if (ClockwiseRotationDistance > AntiClockwiseRotationDistance)
    {
        bIsClockwise = false;
        const float AntiClockwiseCalc = AntiClockwiseRotationDistance / FloatValue;

        if (AntiClockwiseCalc <= 1)
        {
            bIsInRadarSigth = true;

            const float LerpValue = FMath::Lerp(0, MaxWidgetTranslation, AntiClockwiseCalc);
            const float InvertedLerpValue = LerpValue * -1;

            return FVector2D(InvertedLerpValue, 0);
        }

        bIsInRadarSigth = false;
        return FVector2D(0, 0);
    }

    bIsClockwise = true;

    float ClockwiseCalc = ClockwiseRotationDistance / FloatValue;

    if (ClockwiseCalc <= 1)
    {
        bIsInRadarSigth = true;

        const float LerpValue = FMath::Lerp(0, MaxWidgetTranslation, ClockwiseCalc);
        return FVector2d(LerpValue, 0);
    }

    bIsInRadarSigth = false;
    return FVector2d(0, 0);
}

TArray<FMDDirectionInfo> UMDCompassSubsystem::GetDirections() const
{
    return Directions;
}

TArray<FMDMarkerInfo> UMDCompassSubsystem::GetMarkers() const
{
    return Markers;
}

int UMDCompassSubsystem::UpdateMarkerDistance(FMDMarkerInfo MarkerToCalculate) const
{
    const FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();

    const FVector MarkerLocation = FVector(MarkerToCalculate.Location.X, MarkerToCalculate.Location.Y, 0);
    const FVector DistanceVector = MarkerLocation - FVector(PlayerLocation.X, PlayerLocation.Y, 0);

    const float DistanceInMeters = DistanceVector.Length() / UnitsPerMeter;

    return FMath::Floor(DistanceInMeters);
}

void UMDCompassSubsystem::AddMarkerToCompass(FMDMarkerInfo TargetMarker)
{
    Markers.Add(TargetMarker);

    OnAddMarkerToCompass.Broadcast(TargetMarker);
}

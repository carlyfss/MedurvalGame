// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Subsystems/CCompassSubsystem.h"
#include "Subsystems/GameInstanceSubsystem.h"

void UCCompassSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
    FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &UCCompassSubsystem::UpdateAllWidgets);
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, TimerInterval, true);
}

void UCCompassSubsystem::Deinitialize()
{
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
}

float UCCompassSubsystem::RotationToCircleDegrees(float In) const
{
    float SelectedFloat = In;

    if (In < 0)
    {
        const int InIntValue = FMath::Floor(In);
        SelectedFloat = (CircleDegrees + InIntValue) % CircleDegrees;
    }

    return SelectedFloat;
}

float UCCompassSubsystem::GetDeltaClockwise(float A, float B, bool bIsClockwise) const
{
    float AInput = FMath::FloorToInt(A) % CircleDegrees;
    float BInput = FMath::FloorToInt(B) % CircleDegrees;

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

FVector2D UCCompassSubsystem::RotationsToTranslations(FRotator RotationA, FRotator RotationB, bool &bIsClockwise, bool &bIsInRadarSigth) const
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

void UCCompassSubsystem::SetDirections(TArray<FCDirectionInfo> DirectionInfos)
{
    Directions = DirectionInfos;
}

TArray<FCDirectionInfo> UCCompassSubsystem::GetDirections()
{
    return Directions;
}

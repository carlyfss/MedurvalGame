// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/CBLineTraceComponent.h"

UCBLineTraceComponent::UCBLineTraceComponent()
{
    LineTraceCompletedDelegate.BindUObject(this, &UCBLineTraceComponent::OnLineTraceCompleted);
}

void UCBLineTraceComponent::BeginPlay()
{
    Super::BeginPlay();

    const FTimerDelegate TraceDelegate = FTimerDelegate::CreateUObject(this, &UCBLineTraceComponent::CastLineTrace);

    GetWorld()->GetTimerManager().SetTimer(TimerHandle, TraceDelegate, TimerInterval, true);
}

AActor *UCBLineTraceComponent::GetLineTraceHitActor() const
{
    return LineTraceHitActor;
}

FTraceHandle UCBLineTraceComponent::RequestLineTrace()
{
    FVector Location;
    FRotator Rotation;

    PlayerController->GetPlayerViewPoint(Location, Rotation);

    FVector Start = Location;
    FVector End = Start + (Rotation.Vector() * LineTraceDistance);

    FCollisionQueryParams TraceParams;

    FCollisionResponseParams Params = FCollisionResponseParams::DefaultResponseParam;
    Params.CollisionResponse.SetAllChannels(ECR_Ignore);

    if (CollisionChannels.Num() > 0)
    {
        for (ECollisionChannel CollisionChannel : CollisionChannels)
        {
            Params.CollisionResponse.SetResponse(CollisionChannel, ECR_Block);
        }
    }

    return GetWorld()->AsyncLineTraceByChannel(EAsyncTraceType::Single, Start, End, ECC_Visibility, TraceParams,
                                               Params, &LineTraceCompletedDelegate);
}

void UCBLineTraceComponent::CastLineTrace()
{
    if (!bIsLineTraceEnabled)
    {
        return;
    }

    if (!GetWorld()->IsTraceHandleValid(LastTraceHandle, false) && !bIsToCastLineTrace)
    {
        bIsToCastLineTrace = true;
        return;
    }

    if (!bIsToCastLineTrace)
        return;

    if (!IsValid(PlayerController))
        return;

    if (bUseMouseLocation)
    {
        FHitResult HitResult;
        PlayerController->GetHitResultUnderCursor(ECC_GameTraceChannel4, false, HitResult);

        HandleLineTraceResults(HitResult);

        return;
    }

    if (LastTraceHandle._Data.FrameNumber != 0)
    {
        FTraceDatum OutData;

        if (GetWorld()->QueryTraceData(LastTraceHandle, OutData))
        {
            // Clear out handle so next tick we don't enter
            LastTraceHandle._Data.FrameNumber = 0;

            // trace is finished, do stuff with results
            HandleLineTraceResults(OutData);
        }

        return;
    }

    LastTraceHandle = RequestLineTrace();
    bIsToCastLineTrace = false;
}

void UCBLineTraceComponent::OnLineTraceCompleted(const FTraceHandle &TraceHandle, FTraceDatum &TraceResult)
{
}

void UCBLineTraceComponent::HandleLineTraceResults(const FTraceDatum &TraceResult)
{
}

void UCBLineTraceComponent::HandleLineTraceResults(const FHitResult &TraceResult)
{
    AActor *HitActor = TraceResult.GetActor();
    if (IsValid(HitActor))
    {
        if (bActivateLineTraceHitBox)
        {
            DrawDebugBox(GetWorld(), TraceResult.ImpactPoint, FVector(5), FColor::Emerald, false, 0.25f);
        }

        LineTraceHitActor = HitActor;
        return;
    }

    LineTraceHitActor = nullptr;
}

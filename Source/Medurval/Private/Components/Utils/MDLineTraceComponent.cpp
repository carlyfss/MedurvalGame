// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Components/Utils/MDLineTraceComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/MDInteractableInterface.h"

void UMDLineTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLineTrace_Implementation();
	TraceDelegate.BindUObject(this, &UMDLineTraceComponent::OnLineTraceCompleted);
}

void UMDLineTraceComponent::CastLineTrace()
{
	if (!GetWorld()->IsTraceHandleValid(LastTraceHandle, false) && !bIsLineTraceEnabled)
	{
		bIsLineTraceEnabled = true;

		return;
	}

	if (bIsLineTraceEnabled)
	{
		if (IsValid(PlayerController))
		{
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
			bIsLineTraceEnabled = false;
		}
	}
}

FTraceHandle UMDLineTraceComponent::RequestLineTrace()
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
																						 Params, &TraceDelegate);
}

void UMDLineTraceComponent::OnLineTraceCompleted(const FTraceHandle &TraceHandle, FTraceDatum &TraceResult)
{
	ensure(TraceHandle == LastTraceHandle);
	HandleLineTraceResults(TraceResult);
	LastTraceHandle._Data.FrameNumber = 0;
}

void UMDLineTraceComponent::HandleLineTraceResults(const FTraceDatum &TraceResult)
{
	if (bActivateLineTraceDebug)
	{
		DrawDebugLine(GetWorld(), TraceResult.Start, TraceResult.End, FColor::Orange, false, 0.5f);
	}

	if (LineTraceHitActor)
	{
		IMDInteractableInterface *Interactable = Cast<IMDInteractableInterface>(LineTraceHitActor);

		if (Interactable)
		{
			Interactable->OnEndFocus_Implementation();
			LineTraceHitActor = nullptr;
		}
	}

	if (TraceResult.OutHits.Num() <= 0)
		return;

	if (bActivateLineTraceHitBox)
	{
		DrawDebugBox(GetWorld(), TraceResult.OutHits[0].ImpactPoint, FVector(5), FColor::Emerald, false, 0.25f);
	}

	LineTraceHitActor = TraceResult.OutHits[0].GetActor();

	if (!LineTraceHitActor)
		return;

	IMDInteractableInterface *Interactable = Cast<IMDInteractableInterface>(LineTraceHitActor);

	if (!Interactable)
		return;

	Interactable->OnStartFocus_Implementation();
}

void UMDLineTraceComponent::StartLineTrace_Implementation()
{
	bIsLineTraceEnabled = true;
	if (!LineTraceTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(LineTraceTimerHandle, this, &UMDLineTraceComponent::CastLineTrace,
																					 LineTraceInterval, true);
	}
}

void UMDLineTraceComponent::EndLineTrace_Implementation()
{
	if (LineTraceTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(LineTraceTimerHandle);

		LineTraceTimerHandle.Invalidate();
	}

	bIsLineTraceEnabled = false;
	LineTraceHitActor = nullptr;
}

AActor *UMDLineTraceComponent::GetLineTraceHitActor_Implementation() const
{
	return LineTraceHitActor;
}

bool UMDLineTraceComponent::IsLineTraceEnabled_Implementation() const
{
	return bIsLineTraceEnabled;
}

void UMDLineTraceComponent::SetPlayerController(APlayerController *PlayerControl)
{
	PlayerController = PlayerControl;
}
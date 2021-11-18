// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "LineTraceComponent.h"
#include "DrawDebugHelpers.h"

ULineTraceComponent::ULineTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickInterval = 0.075f;
}

void ULineTraceComponent::CastLineTrace()
{
	if (bIsLineTraceEnabled)
	{
		if (IsValid(PlayerController))
		{
			FVector Location;
			FRotator Rotation;
			FHitResult Hit;

			PlayerController->GetPlayerViewPoint(Location, Rotation);

			FVector Start = Location;
			FVector End = Start + (Rotation.Vector() * LineTraceDistance);

			FCollisionQueryParams TraceParams;

			bool bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

			// Enable debug line
			//DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.f);

			if (bHit)
			{
				//DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5), FColor::Emerald, false, 0.25f);

				if (IsValid(Hit.GetActor()))
				{
					LineTraceHitActor = Hit.GetActor();
				}
			} else
			{
				LineTraceHitActor = nullptr;
			}
		}
	}
}

void ULineTraceComponent::StartLineTrace_Implementation()
{
	bIsLineTraceEnabled = true;

	GetWorld()->GetTimerManager().SetTimer(LineTraceTimerHandle, this, &ULineTraceComponent::CastLineTrace,
	                                       LineTraceInterval, true);
}

void ULineTraceComponent::EndLineTrace_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(LineTraceTimerHandle);

	bIsLineTraceEnabled = false;

	LineTraceHitActor = nullptr;
}

AActor* ULineTraceComponent::GetLineTraceHitActor_Implementation() const
{
	return LineTraceHitActor;
}

bool ULineTraceComponent::IsLineTraceEnabled_Implementation() const
{
	return bIsLineTraceEnabled;
}

void ULineTraceComponent::SetPlayerController(APlayerController* PlayerControl)
{
	PlayerController = PlayerControl;
}

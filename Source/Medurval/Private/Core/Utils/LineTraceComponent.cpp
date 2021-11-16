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

			UE_LOG(LogTemp, Warning, TEXT("Casting"));
			
			DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 2.f);

			if (bHit)
			{
				DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5), FColor::Emerald, false, 2.0f);

				if (IsValid(Hit.GetActor()))
				{
					LineTraceHitActor = Hit.GetActor();
				}
			}
		}
	}
}

void ULineTraceComponent::StartLineTrace_Implementation()
{
	bIsLineTraceEnabled = true;

	UE_LOG(LogTemp, Warning, TEXT("Start cast"));
	
	GetWorld()->GetTimerManager().SetTimer(LineTraceTimerHandle, this, &ULineTraceComponent::CastLineTrace, 0.1f, true);
}

void ULineTraceComponent::EndLineTrace_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(LineTraceTimerHandle);

	bIsLineTraceEnabled = false;

	LineTraceHitActor = nullptr;
}

AActor* ULineTraceComponent::GetLineTraceHitActor_Implementation()
{
	return LineTraceHitActor;
}

void ULineTraceComponent::SetPlayerController(APlayerController* PlayerControl)
{
	PlayerController = PlayerControl;
}



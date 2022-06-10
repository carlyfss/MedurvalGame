// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Components/Utils/MDLineTraceComponent.h"
#include "DrawDebugHelpers.h"
#include "Interfaces/MDInteractableInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Macros/PrintString.h"

UMDLineTraceComponent::UMDLineTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickInterval = 0.075f;
}

void UMDLineTraceComponent::CastLineTrace()
{
	if (bIsLineTraceEnabled)
	{
		if (IsValid(PlayerController))
		{
			FVector Location;
			FRotator Rotation;
			FHitResult Hit;
			bool bHit;

			if (bUseMouseLocation)
			{
				TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

				ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery8);
				
				bHit = PlayerController->GetHitResultUnderCursorForObjects(ObjectTypes, false, Hit);	
			} else
			{
				PlayerController->GetPlayerViewPoint(Location, Rotation);

				FVector Start = Location;
				FVector End = Start + (Rotation.Vector() * LineTraceDistance);

				FCollisionQueryParams TraceParams;

				bHit = GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, TraceParams);

				// Enable debug line
				if (bActivateLineTraceDebug)
				{
					DrawDebugLine(GetWorld(), Start, End, FColor::Orange, false, 0.5f);	
				}
			}

			if (bHit)
			{
				// Enable debug hit location
				if (bActivateLineTraceHitBox)
				{
					DrawDebugBox(GetWorld(), Hit.ImpactPoint, FVector(5), FColor::Emerald, false, 0.25f);	
				}

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

void UMDLineTraceComponent::StartLineTrace_Implementation()
{
	bIsLineTraceEnabled = true;

	OverlapedActorsCount++;

	if (!LineTraceTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().SetTimer(LineTraceTimerHandle, this, &UMDLineTraceComponent::CastLineTrace,
										   LineTraceInterval, true);
	}
}

void UMDLineTraceComponent::EndLineTrace_Implementation()
{
	OverlapedActorsCount--;

	if (OverlapedActorsCount == 0)
	{
		if (LineTraceTimerHandle.IsValid())
		{
			GetWorld()->GetTimerManager().ClearTimer(LineTraceTimerHandle);

			LineTraceTimerHandle.Invalidate();
		}
		
		bIsLineTraceEnabled = false;

		LineTraceHitActor = nullptr;
	}
}

AActor* UMDLineTraceComponent::GetLineTraceHitActor_Implementation() const
{
	return LineTraceHitActor;
}

bool UMDLineTraceComponent::IsLineTraceEnabled_Implementation() const
{
	return bIsLineTraceEnabled;
}

void UMDLineTraceComponent::SetPlayerController(APlayerController* PlayerControl)
{
	PlayerController = PlayerControl;
}

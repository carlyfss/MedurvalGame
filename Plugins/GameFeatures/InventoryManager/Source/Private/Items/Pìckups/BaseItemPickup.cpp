// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/BaseItemPickup.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"

ABaseItemPickup::ABaseItemPickup()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	PickupRange = CreateDefaultSubobject<USphereComponent>("PickupRange");
	PickupRange->PrimaryComponentTick.bStartWithTickEnabled = false;
	PickupRange->PrimaryComponentTick.bCanEverTick = false;
	PickupRange->SetupAttachment(RootComponent);

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &ABaseItemPickup::OnComponentBeginOverlap);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	PickupMesh->PrimaryComponentTick.bCanEverTick = false;
	PickupMesh->SetGenerateOverlapEvents(false);
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	PickupMesh->SetupAttachment(PickupRange);
}

void ABaseItemPickup::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseItemPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                                int32 OtherBodyIndex,
                                                bool bFromSweep, const FHitResult& SweepResult)
{
	UActorComponent* InventoryComp = OtherActor->GetComponentByClass(UInventoryComponent::StaticClass());

	if (IsValid(InventoryComp))
	{
		UInventoryComponent* InventoryRef = Cast<UInventoryComponent>(InventoryComp);

		if (IsValid(InventoryRef))
		{
			int Rest = 0;
			
			const bool bAddedItem = InventoryRef->AddItem(ItemData->GetClass(), AmountToAdd, Rest);
			
			if (bAddedItem)
			{
				if (Rest > 0)
				{
					AmountToAdd = Rest;
				}
				else
				{
					Destroy();
				}
			}
		}
	}
}

void ABaseItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	PickupRange->SetSphereRadius(PickupRangeRadius);
	
	if (IsValid(ItemData))
	{
		PickupMesh->SetStaticMesh(ItemData->ItemMesh);
	}
	
}

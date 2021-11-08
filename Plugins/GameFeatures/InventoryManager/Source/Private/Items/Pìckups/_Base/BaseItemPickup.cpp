// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/_Base/BaseItemPickup.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Items/_Base/BaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"

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
}

void ABaseItemPickup::BeginPlay()
{
	Super::BeginPlay();

	bIsPickupReady = ConstructPickupItem();
}

bool ABaseItemPickup::ConstructPickupItem()
{
	UBaseItemDA* Item = Cast<UBaseItemDA>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData));

	if (Item)
	{
		UStaticMesh* Mesh = Cast<UStaticMesh>(
			UKismetSystemLibrary::LoadAsset_Blocking(Item->ItemMesh));

		if (Mesh)
		{
			PickupMesh->SetStaticMesh(Mesh);
			PickupMesh->AttachToComponent(PickupRange, FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			                              NAME_None);

			return true;
		}
	}

	return false;
}

void ABaseItemPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                              AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                              int32 OtherBodyIndex,
                                              bool bFromSweep, const FHitResult& SweepResult)
{
	UActorComponent* InventoryComp = OtherActor->GetComponentByClass(UInventoryComponent::StaticClass());

	if (IsValid(InventoryComp) && bIsPickupReady)
	{
		UInventoryComponent* InventoryRef = Cast<UInventoryComponent>(InventoryComp);

		if (IsValid(InventoryRef) && ItemData.IsValid())
		{
			int Rest = 0;

			UE_LOG(LogTemp, Warning, TEXT("Adding item..."));

			const bool bAddedItem = InventoryRef->AddItem(ItemData, AmountToAdd, Rest);

			UE_LOG(LogTemp, Warning, TEXT("Amount index 0: %i"), InventoryRef->GetAmountAtIndex(1));

			if (bAddedItem)
			{
				UE_LOG(LogTemp, Warning, TEXT("Added item"));
				if (Rest > 0)
				{
					AmountToAdd = Rest;
				}
				else
				{
					Destroy();
				}
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Item not added"));
			}
		}
	}
}

void ABaseItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	PickupRange->SetSphereRadius(PickupRangeRadius);
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/_Base/IMItemPickup.h"

#include "Components/CBSphereComponent.h"
#include "Components/CBStaticMeshComponent.h"
#include "Components/IMInventoryComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Items/_Base/IMBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"

AIMItemPickup::AIMItemPickup()
{
	PickupRange = CreateDefaultSubobject<UCBSphereComponent>("PickupRange");
	PickupRange->SetupAttachment(RootComponent);

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &AIMItemPickup::OnComponentBeginOverlap);

	PickupMesh = CreateDefaultSubobject<UCBStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	PickupMesh->SetupAttachment(PickupRange);
	PickupMesh->SetGenerateOverlapEvents(false);
}

void AIMItemPickup::BeginPlay()
{
	Super::BeginPlay();

	LoadPickupItem();
}

void AIMItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIMItemPickup::LoadPickupItem()
{
	UIMBaseItemDA* Item = Cast<UIMBaseItemDA>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData));

	if (Item != nullptr)
	{
		LoadedItem = Item;

		UStaticMesh* Mesh = Cast<UStaticMesh>(
			UKismetSystemLibrary::LoadAsset_Blocking(Item->ItemMesh));

		if (Mesh != nullptr && PickupMesh != nullptr)
		{
			PickupMesh->SetStaticMesh(Mesh);

			bIsPickupReady = true;
		}
	}
	else
	{
		bIsPickupReady = false;
	}
}

void AIMItemPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                            AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                            int32 OtherBodyIndex,
                                            bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapedActor = OtherActor;
}

void AIMItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (PickupRange != nullptr)
	{
		PickupRange->SetSphereRadius(PickupRangeRadius);
	}

	if (DefaultStaticMesh != nullptr && PickupMesh != nullptr)
	{
		PickupMesh->SetStaticMesh(DefaultStaticMesh);
	}
}

void AIMItemPickup::AddItemToInventory()
{
	UActorComponent* ComponentExists = OverlapedActor->GetComponentByClass(UIMInventoryComponent::StaticClass());

	if (ComponentExists)
	{
		IInventoryInterface* InventoryInterface = Cast<IInventoryInterface>(ComponentExists);

		if (InventoryInterface)
		{
			InventoryInterface->OnAddItemToInventory(LoadedItem);
		}
	}
}

void AIMItemPickup::OnInteract_Implementation()
{
	IMDInteractableInterface::OnInteract_Implementation();
}

void AIMItemPickup::OnStartFocus_Implementation()
{
	IMDInteractableInterface::OnStartFocus_Implementation();
}

void AIMItemPickup::OnEndFocus_Implementation()
{
	IMDInteractableInterface::OnEndFocus_Implementation();
}

TSoftObjectPtr<UIMBaseItemDA> AIMItemPickup::GetItemData() const
{
	return ItemData;
}

void AIMItemPickup::OnPickupStartFocus_Implementation()
{
	PickupMesh->SetRenderCustomDepth(true);
}

void AIMItemPickup::OnPickupEndFocus_Implementation()
{
	PickupMesh->SetRenderCustomDepth(false);
}

void AIMItemPickup::OnPickupInteract_Implementation()
{
	ItemData.Reset();

	OverlapedActor = nullptr;
	LoadedItem = nullptr;
	DefaultStaticMesh = nullptr;
	PickupRange = nullptr;

	Destroy();
}

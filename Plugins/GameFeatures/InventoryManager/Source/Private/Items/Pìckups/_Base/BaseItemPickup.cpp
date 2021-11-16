// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/_Base/BaseItemPickup.h"
#include "Components/InventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Items/_Base/BaseItemPrimaryDA.h"
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
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetupAttachment(PickupRange);
	PickupMesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	PickupMesh->PrimaryComponentTick.bCanEverTick = false;
	PickupMesh->SetGenerateOverlapEvents(false);
}

void ABaseItemPickup::BeginPlay()
{
	Super::BeginPlay();

	LoadPickupItem();
}

void ABaseItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ABaseItemPickup::LoadPickupItem()
{
	UBaseItemPrimaryDA* Item = Cast<UBaseItemPrimaryDA>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData));

	if (Item != nullptr)
	{
		LoadedItem = Item;
		
		UStaticMesh* Mesh = Cast<UStaticMesh>(
			UKismetSystemLibrary::LoadAsset_Blocking(Item->ItemMesh));

		if (Mesh != nullptr && PickupMesh != nullptr)
		{
			PickupMesh->SetStaticMesh(Mesh);
			PickupMesh->AttachToComponent(PickupRange, FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			                              NAME_None);

			bIsPickupReady = true;
		}
	} else
	{
		bIsPickupReady = false;
	}
}

void ABaseItemPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                              AActor* OtherActor, UPrimitiveComponent* OtherComp,
                                              int32 OtherBodyIndex,
                                              bool bFromSweep, const FHitResult& SweepResult)
{
	OverlapedActor = OtherActor;
}

void ABaseItemPickup::OnConstruction(const FTransform& Transform)
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

void ABaseItemPickup::AddItemToInventory()
{
	UActorComponent* ComponentExists = OverlapedActor->GetComponentByClass(UInventoryComponent::StaticClass());

	if (ComponentExists)
	{
		IInventoryInterface* InventoryInterface = Cast<IInventoryInterface>(ComponentExists);

		if (InventoryInterface)
		{
			InventoryInterface->OnAddItemToInventory(LoadedItem);
		}
	}
}

void ABaseItemPickup::OnStartPickupFocus_Implementation_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Focus"))
}

void ABaseItemPickup::OnEndPickupFocus_Implementation_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("End Focus"))
}

void ABaseItemPickup::OnInteract_Implementation_Implementation()
{
	AddItemToInventory();
}

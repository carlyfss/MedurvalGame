// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/_Base/IMItemPickup.h"

#include "Components/IMInventoryComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Items/_Base/BaseItemPrimaryDA.h"
#include "Kismet/KismetSystemLibrary.h"

AIMItemPickup::AIMItemPickup()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.TickInterval = 0.075f;

	

	PickupRange = CreateDefaultSubobject<USphereComponent>("PickupRange");
	PickupRange->PrimaryComponentTick.bStartWithTickEnabled = false;
	PickupRange->PrimaryComponentTick.bCanEverTick = false;
	PickupRange->SetupAttachment(RootComponent);

	PickupRange->OnComponentBeginOverlap.AddDynamic(this, &AIMItemPickup::OnComponentBeginOverlap);

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupMesh->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	PickupMesh->SetupAttachment(PickupRange);
	PickupMesh->PrimaryComponentTick.bStartWithTickEnabled = false;
	PickupMesh->PrimaryComponentTick.bCanEverTick = false;
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
	UBaseItemPrimaryDA* Item = Cast<UBaseItemPrimaryDA>(UKismetSystemLibrary::LoadAsset_Blocking(ItemData));

	if (Item != nullptr)
	{
		LoadedItem = Item;
		
		UStaticMesh* Mesh = Cast<UStaticMesh>(
			UKismetSystemLibrary::LoadAsset_Blocking(Item->ItemMesh));

		if (Mesh != nullptr && PickupMesh != nullptr)
		{
			PickupMesh->SetStaticMesh(Mesh);
			// PickupMesh->AttachToComponent(PickupRange, FAttachmentTransformRules::SnapToTargetNotIncludingScale,
			//                               NAME_None);

			bIsPickupReady = true;
		}
	} else
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

TSoftObjectPtr<UBaseItemPrimaryDA> AIMItemPickup::GetItemData() const
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

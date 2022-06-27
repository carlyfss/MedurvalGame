// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/_Base/IMItemPickup.h"

#include "Components/CBSphereComponent.h"
#include "Components/CBStaticMeshComponent.h"
#include "Components/IMInventoryComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "GameFramework/Character.h"
#include "Items/_Base/IMBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"

AIMItemPickup::AIMItemPickup()
{
	PickupMesh = CreateDefaultSubobject<UCBStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetGenerateOverlapEvents(false);
	PickupMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PickupLoadRange = CreateDefaultSubobject<UCBSphereComponent>("PickupLoadRange");
	PickupLoadRange->SetSphereRadius(200.f);
	PickupLoadRange->ShapeColor = FColor::Blue;
	PickupLoadRange->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupLoadRange->AttachToComponent(PickupMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PickupLoadRange->OnComponentBeginOverlap.AddDynamic(this, &AIMItemPickup::OnBeginOverlap);
	PickupLoadRange->OnComponentEndOverlap.AddDynamic(this, &AIMItemPickup::OnEndOverlap);
}

void AIMItemPickup::BeginPlay()
{
	Super::BeginPlay();

	TimerInterval = 3;
	TimerStartDelay = 3;
}

void AIMItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIMItemPickup::OnPickupItemLoaded()
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager) return;

	LoadedItem = Cast<UIMBaseItemDA>(AssetManager->GetPrimaryAssetObject(ItemId));

	if (!LoadedItem) return;

	UStaticMesh* Mesh = LoadedItem->Mesh.Get();

	if (Mesh)
	{
		PickupMesh->SetStaticMesh(Mesh);
	}
}

void AIMItemPickup::LoadPickupItem()
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager) return;

	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);

	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &AIMItemPickup::OnPickupItemLoaded);

	AssetManager->LoadPrimaryAsset(ItemId, BundlesToLoad, Delegate);
}

void AIMItemPickup::UnloadPickupItem()
{
	UMedurvalAssetManager* AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

	if (!AssetManager) return;

	AssetManager->UnloadPrimaryAsset(ItemId);

	LoadedItem = nullptr;
	PickupMesh->SetStaticMesh(nullptr);
}

void AIMItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	PickupLoadRange->SetSphereRadius(PickupLoadRangeRadius);
}

void AIMItemPickup::AddItemToInventory(AActor* ActorToAddItem)
{
	UActorComponent* ComponentExists = ActorToAddItem->GetComponentByClass(UIMInventoryComponent::StaticClass());

	if (ComponentExists)
	{
		IInventoryInterface* InventoryInterface = Cast<IInventoryInterface>(ComponentExists);

		if (InventoryInterface)
		{
			bool bAddedSuccessfully = InventoryInterface->OnAddItemToInventory_Implementation(ItemId);

			if (!bAddedSuccessfully) return;

			MarkPickupForGarbage();
			MarkAsGarbage();
		}
	}
}

void AIMItemPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		const UActorComponent* ComponentExists = OtherActor->GetComponentByClass(UIMInventoryComponent::StaticClass());

		if (!ComponentExists) return;

		LoadPickupItem();
	}
}

void AIMItemPickup::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UnloadPickupItem();
}

void AIMItemPickup::OnInteract_Implementation(AActor* InstigatorActor)
{
	IMDInteractableInterface::OnInteract_Implementation(InstigatorActor);
	AddItemToInventory(InstigatorActor);
}

void AIMItemPickup::OnStartFocus_Implementation()
{
	IMDInteractableInterface::OnStartFocus_Implementation();
	OnPickupStartFocus();
}

void AIMItemPickup::OnEndFocus_Implementation()
{
	IMDInteractableInterface::OnEndFocus_Implementation();
	OnPickupEndFocus();
}

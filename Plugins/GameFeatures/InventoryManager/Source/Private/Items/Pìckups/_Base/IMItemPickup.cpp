// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Items/Pìckups/_Base/IMItemPickup.h"

#include "Components/CBStaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Controller/MDPlayerController.h"
#include "GameFramework/Character.h"
#include "Items/_Base/IMBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"

AIMItemPickup::AIMItemPickup()
{
	PickupMesh = CreateDefaultSubobject<UCBStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetGenerateOverlapEvents(false);
}

void AIMItemPickup::BeginPlay()
{
	Super::BeginPlay();

	bIsToLoopTimer = true;
	TimerInterval = 2.f;
	StartTimerWithDelegate();

	LoadPickupItem();
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

	bIsPickupReady = true;

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

void AIMItemPickup::TimerDelegate()
{
	Super::TimerDelegate();

	FVector PlayerLocation = GetWorld()->GetFirstPlayerController()->GetCharacter()->GetActorLocation();
	double DistanceToPlayer = FVector::Distance(this->GetActorLocation(), PlayerLocation);

	UE_LOG(LogTemp, Log, TEXT("Distance: %f"), DistanceToPlayer);
}

void AIMItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

void AIMItemPickup::AddItemToInventory()
{
	// UActorComponent* ComponentExists = OverlapedActor->GetComponentByClass(UIMInventoryComponent::StaticClass());
	//
	// // Unload the Item World Bundle
	//
	// // Load the Item UI Bundle
	//
	// if (ComponentExists)
	// {
	// 	IInventoryInterface* InventoryInterface = Cast<IInventoryInterface>(ComponentExists);
	//
	// 	if (InventoryInterface)
	// 	{
	// 		InventoryInterface->OnAddItemToInventory(LoadedItem);
	// 	}
	// }
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
	LoadedItem = nullptr;

	Destroy();
}

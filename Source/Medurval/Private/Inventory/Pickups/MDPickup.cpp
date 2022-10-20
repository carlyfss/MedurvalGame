// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Inventory/Pickups/MDPickup.h"

#include "Inventory/Components/MDInventoryComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Components/MDCapsuleComponent.h"
#include "Core/Components/MDSphereComponent.h"
#include "Core/Components/MDStaticMeshComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Items/MDItemDataAsset.h"
#include "Kismet/KismetSystemLibrary.h"

AMDPickup::AMDPickup()
{
	PickupMesh = CreateDefaultSubobject<UMDStaticMeshComponent>("PickupMesh");
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PickupMesh->SetGenerateOverlapEvents(false);
	PickupMesh->SetupAttachment(RootComponent);

	PickupLoadRange = CreateDefaultSubobject<UMDSphereComponent>("PickupLoadRange");
	PickupLoadRange->SetSphereRadius(500.f);
	PickupLoadRange->ShapeColor = FColor(30, 30, 200, 15);
	PickupLoadRange->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupLoadRange->SetupAttachment(PickupMesh);
	PickupLoadRange->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupLoadRange->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PickupLoadRange->OnComponentBeginOverlap.AddDynamic(this, &AMDPickup::OnBeginOverlap);
	PickupLoadRange->OnComponentEndOverlap.AddDynamic(this, &AMDPickup::OnEndOverlap);

	PickupCollision = CreateDefaultSubobject<UMDCapsuleComponent>("PickupCollision");
	PickupCollision->ShapeColor = FColor(100, 0, 200, 50);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetupAttachment(PickupMesh);

	PickupCollision->SetCollisionObjectType(ECC_GameTraceChannel3);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AMDPickup::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AMDPickup::CheckForOverlappedActors);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, 0.1f, false);
}

void AMDPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMDPickup::OnPickupItemLoaded()
{
	LoadedItem = Cast<UMDItemDataAsset>(GetMDGameInstance()->GetMedurvalAssetManager()->GetPrimaryAssetObject(ItemId));

	if (!LoadedItem)
		return;

	UStaticMesh* Mesh = LoadedItem->Mesh.Get();

	if (Mesh)
	{
		PickupMesh->SetStaticMesh(Mesh);
	}

	CalculateCollisionSize();
}

void AMDPickup::CheckForOverlappedActors()
{
	TArray<AActor*> OverlappedActors;
	TSubclassOf<AMDPlayerCharacter> PlayerClass;
	PickupLoadRange->GetOverlappingActors(OverlappedActors, PlayerClass);

	if (OverlappedActors.Num() > 0)
	{
		LoadPickupItem();
	}
}

void AMDPickup::LoadPickupItem()
{
	TArray<FName> BundlesToLoad;
	BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);
	
	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &AMDPickup::OnPickupItemLoaded);
	GetMDGameInstance()->LoadPrimaryAssetId(ItemId, Delegate, BundlesToLoad);

	OnItemLoaded.Broadcast();
}

void AMDPickup::UnloadPickupItem()
{
	GetMDGameInstance()->GetMedurvalAssetManager()->UnloadPrimaryAsset(ItemId);

	LoadedItem = nullptr;
	PickupMesh->SetStaticMesh(nullptr);
	OnItemUnloaded.Broadcast();
}

void AMDPickup::CalculateCollisionSize()
{
	FVector Min;
	FVector Max;
	PickupMesh->GetLocalBounds(Min, Max);

	FVector MeshSize = Max - Min;

	float MeshX = (MeshSize.X + PickupCollisionOffset) / 2;
	float MeshZ = (MeshSize.Z + PickupCollisionOffset) / 2;

	if (bIsCollisionUp)
	{
		PickupCollision->SetCapsuleHalfHeight(MeshZ);
		PickupCollision->SetCapsuleRadius(MeshX);
	}
	else
	{
		const FRotator Rotation = PickupCollision->GetComponentRotation();
		PickupCollision->SetWorldRotation(FRotator(90, Rotation.Yaw, Rotation.Roll));

		int32 MeshZHalfSize = MeshZ / 2;
		PickupCollision->AddLocalOffset(FVector(MeshZHalfSize, 0, 0));
		PickupCollision->SetCapsuleHalfHeight(MeshX);
		PickupCollision->SetCapsuleRadius(MeshZ);
	}
}

void AMDPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	PickupLoadRange->SetSphereRadius(PickupLoadRangeRadius);
}

void AMDPickup::AddItemToInventory(AActor* ActorToAddItem)
{
	UActorComponent* ComponentExists = ActorToAddItem->GetComponentByClass(UMDInventoryComponent::StaticClass());

	if (ComponentExists)
	{
		IMDInventoryInterface* InventoryInterface = Cast<IMDInventoryInterface>(ComponentExists);

		if (InventoryInterface)
		{
			const bool bAddedSuccessfully = InventoryInterface->
				OnAddItemToInventory_Implementation(ItemId, AmountToAdd);

			if (!bAddedSuccessfully)
				return;

			MarkPickupForGarbage();
			MarkAsGarbage();
			Destroy();
		}
	}
}

void AMDPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                               UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                               const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		const UActorComponent* ComponentExists = OtherActor->GetComponentByClass(UMDInventoryComponent::StaticClass());

		if (!ComponentExists)
			return;

		LoadPickupItem();
	}
}

void AMDPickup::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UnloadPickupItem();
}

void AMDPickup::OnInteract_Implementation(AActor* InstigatorActor)
{
	IMDInteractableInterface::OnInteract_Implementation(InstigatorActor);
	AddItemToInventory(InstigatorActor);
}

void AMDPickup::OnStartFocus_Implementation()
{
	IMDInteractableInterface::OnStartFocus_Implementation();
	OnPickupStartFocus();
}

void AMDPickup::OnEndFocus_Implementation()
{
	IMDInteractableInterface::OnEndFocus_Implementation();
	OnPickupEndFocus();
}

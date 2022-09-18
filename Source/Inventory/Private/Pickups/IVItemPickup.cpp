// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Pickups/IVItemPickup.h"

#include "Components/IVInventoryComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Components/MDCapsuleComponent.h"
#include "Core/Components/MDSphereComponent.h"
#include "Core/Components/MDStaticMeshComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Items/IVBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"

AIVItemPickup::AIVItemPickup()
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

	PickupLoadRange->OnComponentBeginOverlap.AddDynamic(this, &AIVItemPickup::OnBeginOverlap);
	PickupLoadRange->OnComponentEndOverlap.AddDynamic(this, &AIVItemPickup::OnEndOverlap);

	PickupCollision = CreateDefaultSubobject<UMDCapsuleComponent>("PickupCollision");
	PickupCollision->ShapeColor = FColor(100, 0, 200, 50);
	PickupCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PickupCollision->SetupAttachment(PickupMesh);

	PickupCollision->SetCollisionObjectType(ECC_GameTraceChannel3);
	PickupCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	PickupCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AIVItemPickup::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	FTimerDelegate Delegate = FTimerDelegate::CreateUObject(this, &AIVItemPickup::CheckForOverlappedActors);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Delegate, 0.1f, false);
}

void AIVItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIVItemPickup::OnPickupItemLoaded()
{
	LoadedItem = Cast<UIVBaseItemDA>(GetMDGameInstance()->GetMedurvalAssetManager()->GetPrimaryAssetObject(ItemId));

	if (!LoadedItem)
		return;

	UStaticMesh* Mesh = LoadedItem->Mesh.Get();

	if (Mesh)
	{
		PickupMesh->SetStaticMesh(Mesh);
	}

	CalculateCollisionSize();
}

void AIVItemPickup::CheckForOverlappedActors()
{
	TArray<AActor*> OverlappedActors;
	TSubclassOf<AMDPlayerCharacter> PlayerClass;
	PickupLoadRange->GetOverlappingActors(OverlappedActors, PlayerClass);

	if (OverlappedActors.Num() > 0)
	{
		LoadPickupItem();
	}
}

void AIVItemPickup::LoadPickupItem()
{
	FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &AIVItemPickup::OnPickupItemLoaded);
	GetMDGameInstance()->LoadPrimaryAssetId(ItemId, Delegate);

	OnItemLoaded.Broadcast();
}

void AIVItemPickup::UnloadPickupItem()
{
	GetMDGameInstance()->GetMedurvalAssetManager()->UnloadPrimaryAsset(ItemId);

	LoadedItem = nullptr;
	PickupMesh->SetStaticMesh(nullptr);
	OnItemUnloaded.Broadcast();
}

void AIVItemPickup::CalculateCollisionSize()
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

		PickupCollision->SetCapsuleHalfHeight(MeshX);
		PickupCollision->SetCapsuleRadius(MeshZ);
	}
}

void AIVItemPickup::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	PickupLoadRange->SetSphereRadius(PickupLoadRangeRadius);
}

void AIVItemPickup::AddItemToInventory(AActor* ActorToAddItem)
{
	UActorComponent* ComponentExists = ActorToAddItem->GetComponentByClass(UIVInventoryComponent::StaticClass());

	if (ComponentExists)
	{
		IIVInventoryInterface* InventoryInterface = Cast<IIVInventoryInterface>(ComponentExists);

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

void AIVItemPickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult& SweepResult)
{
	if (IsValid(OtherActor))
	{
		const UActorComponent* ComponentExists = OtherActor->GetComponentByClass(UIVInventoryComponent::StaticClass());

		if (!ComponentExists)
			return;

		LoadPickupItem();
	}
}

void AIVItemPickup::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UnloadPickupItem();
}

void AIVItemPickup::OnInteract_Implementation(AActor* InstigatorActor)
{
	IMDInteractableInterface::OnInteract_Implementation(InstigatorActor);
	AddItemToInventory(InstigatorActor);
}

void AIVItemPickup::OnStartFocus_Implementation()
{
	IMDInteractableInterface::OnStartFocus_Implementation();
	OnPickupStartFocus();
}

void AIVItemPickup::OnEndFocus_Implementation()
{
	IMDInteractableInterface::OnEndFocus_Implementation();
	OnPickupEndFocus();
}

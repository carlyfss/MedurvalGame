// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Pickups/IVItemPickup.h"

#include "Components/CBSphereComponent.h"
#include "Components/CBStaticMeshComponent.h"
#include "Components/IVInventoryComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "GameFramework/Character.h"
#include "Items/IVBaseItemDA.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Medurval/Private/Characters/MDBaseCharacter.h"

AIVItemPickup::AIVItemPickup()
{
    PickupMesh = CreateDefaultSubobject<UCBStaticMeshComponent>("PickupMesh");
    PickupMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    PickupMesh->SetGenerateOverlapEvents(false);
    PickupMesh->SetupAttachment(RootComponent);

    PickupLoadRange = CreateDefaultSubobject<UCBSphereComponent>("PickupLoadRange");
    PickupLoadRange->SetSphereRadius(500.f);
    PickupLoadRange->ShapeColor = FColor::Blue;
    PickupLoadRange->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    PickupLoadRange->SetupAttachment(PickupMesh);

    PickupLoadRange->OnComponentBeginOverlap.AddDynamic(this, &AIVItemPickup::OnBeginOverlap);
    PickupLoadRange->OnComponentEndOverlap.AddDynamic(this, &AIVItemPickup::OnEndOverlap);
}

void AIVItemPickup::BeginPlay()
{
    Super::BeginPlay();

    TimerInterval = 3;
    TimerStartDelay = 3;
}

void AIVItemPickup::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void AIVItemPickup::OnPickupItemLoaded()
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    LoadedItem = Cast<UIVBaseItemDA>(AssetManager->GetPrimaryAssetObject(ItemId));

    if (!LoadedItem)
        return;

    UStaticMesh *Mesh = LoadedItem->Mesh.Get();

    if (Mesh)
    {
        PickupMesh->SetStaticMesh(Mesh);
    }

    SetCollisionSize();
}

void AIVItemPickup::LoadPickupItem()
{
    TArray<AActor*> OverlappingActors;
    PickupLoadRange->GetOverlappingActors(OverlappingActors);
    
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::WorldBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &AIVItemPickup::OnPickupItemLoaded);

    AssetManager->LoadPrimaryAsset(ItemId, BundlesToLoad, Delegate);
}

void AIVItemPickup::UnloadPickupItem()
{
    UMedurvalAssetManager *AssetManager = Cast<UMedurvalAssetManager>(UMedurvalAssetManager::GetIfValid());

    if (!AssetManager)
        return;

    AssetManager->UnloadPrimaryAsset(ItemId);

    LoadedItem = nullptr;
    PickupMesh->SetStaticMesh(nullptr);
}

void AIVItemPickup::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);

    PickupLoadRange->SetSphereRadius(PickupLoadRangeRadius);
}

void AIVItemPickup::AddItemToInventory(AActor *ActorToAddItem)
{
    UActorComponent *ComponentExists = ActorToAddItem->GetComponentByClass(UIVInventoryComponent::StaticClass());

    if (ComponentExists)
    {
        IIVInventoryInterface *InventoryInterface = Cast<IIVInventoryInterface>(ComponentExists);

        if (InventoryInterface)
        {
            const bool bAddedSuccessfully = InventoryInterface->OnAddItemToInventory_Implementation(ItemId, AmountToAdd);

            if (!bAddedSuccessfully)
                return;

            MarkPickupForGarbage();
            MarkAsGarbage();
        }
    }
}

void AIVItemPickup::OnBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
                                   UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                   const FHitResult &SweepResult)
{
    if (IsValid(OtherActor))
    {
        const UActorComponent *ComponentExists = OtherActor->GetComponentByClass(UIVInventoryComponent::StaticClass());

        if (!ComponentExists)
            return;

        LoadPickupItem();
    }
}

void AIVItemPickup::OnEndOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
                                 UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    UnloadPickupItem();
}

void AIVItemPickup::OnInteract_Implementation(AActor *InstigatorActor)
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

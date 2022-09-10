// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Actors/MDActor.h"
#include "Interfaces/MDInteractableInterface.h"
#include "IVItemPickup.generated.h"

class UMDCapsuleComponent;
class UCBSphereComponent;
class UCBStaticMeshComponent;
class UIVBaseItemDA;

UCLASS(meta = (DisplayName = "ItemPickup"))
class AIVItemPickup : public AMDActor, public IMDInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TObjectPtr<UIVBaseItemDA> LoadedItem = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "ItemPickup", meta = (AllowPrivateAccess = true))
	FPrimaryAssetId ItemId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemPickup", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCBStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemPickup", meta = (AllowPrivateAccess = true))
	TObjectPtr<UCBSphereComponent> PickupLoadRange = nullptr;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemPickup", meta = (AllowPrivateAccess = true))
    TObjectPtr<UMDCapsuleComponent> PickupCollision = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ItemPickup", meta = (AllowPrivateAccess = true))
    int PickupCollisionOffset = 10;
    
	UPROPERTY(EditInstanceOnly, Category = "ItemPickup")
	uint8 AmountToAdd = 1;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "ItemPickup", meta = (AllowPrivateAccess = true))
    bool bIsCollisionUp = false;

	UPROPERTY(EditInstanceOnly, Category = "ItemPickup")
	float PickupLoadRangeRadius = 3000.f;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPickupItemLoaded();

	void LoadPickupItem();

	void UnloadPickupItem();

	UFUNCTION(BlueprintImplementableEvent, Category = "ItemPickup")
	void MarkPickupForGarbage();

    void CalculateCollisionSize();

	virtual void OnConstruction(const FTransform &Transform) override;

	void AddItemToInventory(AActor *ActorToAddItem);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
											int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent *OverlappedComp, class AActor *OtherActor,
										class UPrimitiveComponent *OtherComp, int32 OtherBodyIndex);

public:
    AIVItemPickup();
    
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ItemInteraction")
	void OnPickupStartFocus();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ItemInteraction")
	void OnPickupEndFocus();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemPickedUp);
    UPROPERTY(BlueprintAssignable)
    FOnItemPickedUp OnItemPickedUp;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemUnloaded);

    UPROPERTY(BlueprintAssignable)
    FOnItemUnloaded OnItemUnloaded;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnItemLoaded);

    UPROPERTY(BlueprintAssignable)
    FOnItemLoaded OnItemLoaded;

	virtual void OnInteract_Implementation(AActor *InstigatorActor) override;

	virtual void OnStartFocus_Implementation() override;

	virtual void OnEndFocus_Implementation() override;
};

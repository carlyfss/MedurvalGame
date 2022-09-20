// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Actors/MDActor.h"
#include "Core/Interfaces/MDInteractableInterface.h"
#include "MDPickup.generated.h"

class UMDSphereComponent;
class UMDStaticMeshComponent;
class UMDCapsuleComponent;
class UMDItemDataAsset;

UCLASS(meta = (DisplayName = "Pickup"))
class AMDPickup : public AMDActor, public IMDInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TObjectPtr<UMDItemDataAsset> LoadedItem = nullptr;

	UPROPERTY(EditInstanceOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	FPrimaryAssetId ItemId;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDSphereComponent> PickupLoadRange = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	TObjectPtr<UMDCapsuleComponent> PickupCollision = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	int PickupCollisionOffset = 10;

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	uint8 AmountToAdd = 1;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Pickup", meta = (AllowPrivateAccess = true))
	bool bIsCollisionUp = false;

	UPROPERTY(EditInstanceOnly, Category = "Pickup")
	float PickupLoadRangeRadius = 3000.f;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPickupItemLoaded();

	void CheckForOverlappedActors();

	void LoadPickupItem();

	void UnloadPickupItem();

	UFUNCTION(BlueprintImplementableEvent, Category = "Pickup")
	void MarkPickupForGarbage();

	void CalculateCollisionSize();

	virtual void OnConstruction(const FTransform& Transform) override;

	void AddItemToInventory(AActor* ActorToAddItem);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	                  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	AMDPickup();

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

	virtual void OnInteract_Implementation(AActor* InstigatorActor) override;

	virtual void OnStartFocus_Implementation() override;

	virtual void OnEndFocus_Implementation() override;
};

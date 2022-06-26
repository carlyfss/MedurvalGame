// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Actors/CBActor.h"
#include "GameFramework/Actor.h"
#include "Interfaces/MDInteractableInterface.h"
#include "IMItemPickup.generated.h"

class UCBSphereComponent;
class UCBStaticMeshComponent;
class UIMInventoryComponent;
class UIMBaseItemDA;

UCLASS(meta=(DisplayName="InventoryItemPickup"))
class AIMItemPickup : public ACBActor, public IMDInteractableInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	bool bIsPickupReady = false;

	UPROPERTY(Transient)
	TObjectPtr<UIMBaseItemDA> LoadedItem = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup", meta=(AllowPrivateAccess=true))
	FPrimaryAssetId ItemId;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pickup", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCBStaticMeshComponent> PickupMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category="Pickup")
	uint8 AmountToAdd = 1;

public:
	// Sets default values for this actor's properties
	AIMItemPickup();

	TSoftObjectPtr<UIMBaseItemDA> ItemData;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void OnPickupItemLoaded();
	
	void LoadPickupItem();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category="Pickup|Configuration")
	virtual void AddItemToInventory();

	virtual void TimerDelegate() override;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="ItemInteraction")
	void OnPickupStartFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="ItemInteraction")
	void OnPickupEndFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="ItemInteraction")
	void OnPickupInteract();

	virtual void OnInteract_Implementation() override;

	virtual void OnStartFocus_Implementation() override;

	virtual void OnEndFocus_Implementation() override;
};

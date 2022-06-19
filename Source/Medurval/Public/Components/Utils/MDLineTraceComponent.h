// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/CBActorComponent.h"
#include "Interfaces/MDLineTraceInterface.h"
#include "MDLineTraceComponent.generated.h"


UCLASS(ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent))
class MEDURVAL_API UMDLineTraceComponent : public UCBActorComponent, public IMDLineTraceInterface
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	uint8 OverlapedActorsCount = 0;

	UPROPERTY(BlueprintSetter=SetPlayerController, Category="_LineTrace|Configuration")
	TObjectPtr<APlayerController> PlayerController = nullptr;

	/** TODO Remender to add a new visibility channel for the line trace with the inventory items */
	UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
	float LineTraceDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
	float LineTraceInterval = 0.1f;

	/** Whether to use the mouse position on screen if not it will use the player's camera view */
	UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
	bool bUseMouseLocation = false;

	UPROPERTY(BlueprintReadWrite, Category="_LineTrace|Configuration", meta=(AllowPrivateAccess=true))
	bool bIsLineTraceEnabled = false;
	
	TObjectPtr<AActor> LineTraceHitActor = nullptr;

	FTimerHandle LineTraceTimerHandle;

public:
	UPROPERTY(EditAnywhere, Category="_LineTrace|Configuration")
	bool bActivateLineTraceDebug = false;

	UPROPERTY(EditAnywhere, Category="_LineTrace|Configuration")
	bool bActivateLineTraceHitBox = false;

protected:
	
	virtual void CastLineTrace() final;

public:

	virtual void StartLineTrace_Implementation() override;

	virtual void EndLineTrace_Implementation() override;

	virtual AActor* GetLineTraceHitActor_Implementation() const override;

	virtual bool IsLineTraceEnabled_Implementation() const override;

	UFUNCTION(BlueprintCallable, Category="_LineTrace|Configuration")
	void SetPlayerController(APlayerController* PlayerControl);
};

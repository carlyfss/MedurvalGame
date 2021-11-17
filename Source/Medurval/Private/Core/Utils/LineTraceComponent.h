// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/LineTraceInterface.h"
#include "LineTraceComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MEDURVAL_API ULineTraceComponent : public UActorComponent, public ILineTraceInterface
{
	GENERATED_BODY()

	UPROPERTY(BlueprintSetter=SetPlayerController, Category="_LineTrace|Configuration")
	TObjectPtr<APlayerController> PlayerController = nullptr;

	/** TODO Remender to add a new visibility channel for the line trace with the inventory items */
	UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
	float LineTraceDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
	float LineTraceInterval = 0.1f;

	UPROPERTY(BlueprintReadWrite, Category="_LineTrace|Configuration", meta=(AllowPrivateAccess=true))
	bool bIsLineTraceEnabled = false;

	TObjectPtr<AActor> LineTraceHitActor = nullptr;

	FTimerHandle LineTraceTimerHandle;

public:
	// Sets default values for this actor's properties
	ULineTraceComponent();

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

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Core/Components/MDActorComponent.h"
#include "Interfaces/MDLineTraceInterface.h"
#include "MDLineTraceComponent.generated.h"

UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class MEDURVAL_API UMDLineTraceComponent : public UMDActorComponent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintSetter=SetPlayerController, Category="MDLineTraceComponent|Configuration")
    TObjectPtr<APlayerController> PlayerController = nullptr;

    UPROPERTY(EditDefaultsOnly, Category="MDLineTraceComponent|Configuration")
    float LineTraceDistance = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category="MDLineTraceComponent|Configuration")
    float LineTraceInterval = 0.1f;

    /** Whether to use the mouse position on screen if not it will use the player's camera view */
    UPROPERTY(EditDefaultsOnly, Category="MDLineTraceComponent|Configuration")
    bool bUseMouseLocation = false;

    UPROPERTY(BlueprintReadWrite, Category="MDLineTraceComponent|Configuration", meta=(AllowPrivateAccess=true))
    bool bIsLineTraceEnabled = true;

    TObjectPtr<AActor> LineTraceHitActor = nullptr;

    FTimerHandle LineTraceTimerHandle;

    UPROPERTY(EditDefaultsOnly, Category="MDLineTraceComponent|Configuration")
    TArray<TEnumAsByte<ECollisionChannel>> CollisionChannels;

    UPROPERTY(EditDefaultsOnly, Category="MDLineTraceComponent|Configuration")
    TEnumAsByte<ECollisionChannel> CursorCollisionChannel;

public:
    UPROPERTY(EditAnywhere, Category="MDLineTraceComponent|Configuration")
    bool bActivateLineTraceDebug = false;

    UPROPERTY(EditAnywhere, Category="MDLineTraceComponent|Configuration")
    bool bActivateLineTraceHitBox = false;

protected:
    void CastLineTrace();

    FTraceHandle RequestLineTrace();

    FTraceHandle LastTraceHandle;

    FTraceDelegate TraceDelegate;

    void OnLineTraceCompleted(const FTraceHandle &TraceHandle, FTraceDatum &TraceResult);

    void HandleLineTraceResults(const FTraceDatum &TraceResult);

    void HandleLineTraceResults(const FHitResult &TraceResult);

public:
    bool IsLineTraceEnabled() const;
    
    void SetLineTraceEnabled(bool bIsEnabled);

    AActor* GetHitActor() const;

    UFUNCTION(BlueprintCallable, Category="MDLineTraceComponent|Configuration")
    void SetPlayerController(APlayerController *PlayerControl);

    void SetCursorCollisionChannel(TEnumAsByte<ECollisionChannel> CollisionChannel);

    virtual void BeginPlay() override;
};

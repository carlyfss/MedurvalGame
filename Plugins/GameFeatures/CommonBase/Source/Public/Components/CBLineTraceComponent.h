// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Components/CBActorComponent.h"
#include "CBLineTraceComponent.generated.h"

/**
 * 
 */
UCLASS()
class COMMONBASE_API UCBLineTraceComponent : public UCBActorComponent
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="_LineTrace|Configuration", meta=(AllowPrivateAccess=true))
    APlayerController *PlayerController = nullptr;

    UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
    float LineTraceDistance = 500.0f;

    UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
    float TimerInterval = 0.1f;

    UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
    bool bUseMouseLocation = false;

    TObjectPtr<AActor> LineTraceHitActor = nullptr;

    UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
    TArray<TEnumAsByte<ECollisionChannel>> CollisionChannels;

    UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
    bool bActivateLineTraceDebug = false;

    UPROPERTY(EditDefaultsOnly, Category="_LineTrace|Configuration")
    bool bActivateLineTraceHitBox = false;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="_LineTrace|Configuration", meta=(AllowPrivateAccess=true))
    bool bIsToCastLineTrace = true;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category="_LineTrace|Configuration", meta=(AllowPrivateAccess=true))
    bool bIsLineTraceEnabled = true;

    FTraceHandle RequestLineTrace();

    FTraceHandle LastTraceHandle;

    FTraceDelegate LineTraceCompletedDelegate;

    FTimerHandle TimerHandle;

protected:
    void CastLineTrace();

    void OnLineTraceCompleted(const FTraceHandle &TraceHandle, FTraceDatum &TraceResult);

    void HandleLineTraceResults(const FTraceDatum &TraceResult);

    void HandleLineTraceResults(const FHitResult &TraceResult);

public:
    UCBLineTraceComponent();

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintPure, BlueprintCallable, Category="LineTrace")
    AActor *GetLineTraceHitActor() const;
};

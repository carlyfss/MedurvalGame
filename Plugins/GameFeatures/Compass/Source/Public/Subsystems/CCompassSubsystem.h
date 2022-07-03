// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Structs/FCDirectionInfo.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CCompassSubsystem.generated.h"

class UCCompassWidget;
/**
 *
 */
UCLASS(DisplayName = "CompassSubsystem")
class COMPASS_API UCCompassSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

    UPROPERTY(EditDefaultsOnly, Category="Compass|Configurations", meta = (AllowPrivateAccess = true))
    TArray<FCDirectionInfo> Directions;

public:
    UFUNCTION(BlueprintCallable, Category="Compass")
    void SetDirections(TArray<FCDirectionInfo> DirectionInfos);

    UFUNCTION(BlueprintCallable, Category="Compass")
    TArray<FCDirectionInfo> GetDirections();
};

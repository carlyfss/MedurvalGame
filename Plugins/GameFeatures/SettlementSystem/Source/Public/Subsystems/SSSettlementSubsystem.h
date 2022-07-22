// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SSSettlementSubsystem.generated.h"


class USSSettlementComponent;
/**
 *
 */
UCLASS(DisplayName = "SettlementSubsystem")
class SETTLEMENTSYSTEM_API USSSettlementSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

    virtual void Initialize(FSubsystemCollectionBase &Collection) override;

    virtual void Deinitialize() override;

    TArray<TObjectPtr<USSSettlementComponent>> Settlements;

public:
    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    USSSettlementComponent *GetSettlementByOwner(ACharacter *OwnerCharacter) const;

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    TArray<USSSettlementComponent *> GetSettlements() const;

    UFUNCTION(BlueprintCallable, Category="SettlementSubsystem")
    void RegisterNewSettlement(USSSettlementComponent *Settlement);
};

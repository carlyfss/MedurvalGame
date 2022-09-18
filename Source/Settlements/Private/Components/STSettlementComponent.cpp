// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STSettlementComponent.h"

USTSettlementComponent::USTSettlementComponent()
{
    Economy = CreateDefaultSubobject<USTSettlementEconomyComponent>("EconomyComponent");
}

float USTSettlementComponent::GetSettlementRange() const
{
    return SettlementRange;
}

float USTSettlementComponent::GetSettlementSize() const
{
    return SettlementSize;
}

void USTSettlementComponent::SetSettlementOwner(AMDCharacter* SettlementOwner)
{
    Owner = SettlementOwner;
}

AMDCharacter* USTSettlementComponent::GetSettlementOwner() const
{
    return Owner;
}

USTSettlementEconomyComponent *USTSettlementComponent::GetEconomy() const
{
    return Economy;
}

bool USTSettlementComponent::AddNewTerrain(ASTTerrainActor *Terrain)
{
    if (!Terrain)
        return false;

    OwnedTerrains.Add(Terrain);
    return true;
}

void USTSettlementComponent::BeginPlay()
{
    Super::BeginPlay();
}

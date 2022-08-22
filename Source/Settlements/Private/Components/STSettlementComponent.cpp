// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/STSettlementComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

USTSettlementComponent::USTSettlementComponent()
{
    Economy = CreateDefaultSubobject<USTSettlementEconomyComponent>("EconomyComponent");
}

void USTSettlementComponent::SetSettlementOwner(ACharacter *SettlementOwner)
{
    Owner = SettlementOwner;
}

ACharacter *USTSettlementComponent::GetSettlementOwner() const
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

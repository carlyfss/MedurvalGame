// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/SSSettlementComponent.h"

#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/SSSettlementSubsystem.h"

USSSettlementComponent::USSSettlementComponent()
{
    Economy = CreateDefaultSubobject<USSSettlementEconomyComponent>("EconomyComponent");
}

void USSSettlementComponent::SetSettlementOwner(ACharacter *SettlementOwner)
{
    Owner = SettlementOwner;
}

ACharacter *USSSettlementComponent::GetSettlementOwner() const
{
    return Owner;
}

USSSettlementEconomyComponent *USSSettlementComponent::GetEconomy()
{
    return Economy;
}

bool USSSettlementComponent::AddNewTerrain(ASSTerrainActor *Terrain)
{
    if (!Terrain)
        return false;

    OwnedTerrains.Add(Terrain);
    return true;
}

void USSSettlementComponent::BeginPlay()
{
    Super::BeginPlay();
}

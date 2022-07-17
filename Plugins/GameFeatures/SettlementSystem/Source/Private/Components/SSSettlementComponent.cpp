// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Components/SSSettlementComponent.h"

USSSettlementComponent::USSSettlementComponent()
{
    Economy = CreateDefaultSubobject<USSSettlementEconomyComponent>("EconomyComponent");
}

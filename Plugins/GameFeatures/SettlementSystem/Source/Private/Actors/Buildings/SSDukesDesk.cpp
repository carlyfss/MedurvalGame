// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Buildings/SSDukesDesk.h"

#include "Components/SSSettlementComponent.h"

ASSDukesDesk::ASSDukesDesk()
{
    SettlementComponent = CreateDefaultSubobject<USSSettlementComponent>("SettlementComponent");
}

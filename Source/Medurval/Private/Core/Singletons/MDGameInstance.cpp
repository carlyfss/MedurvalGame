// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDGameInstance.h"

#include "Core/Components/Base/MDEconomyComponent.h"
#include "Kismet/GameplayStatics.h"

UMDGameInstance::UMDGameInstance()
{
    Currency = CreateDefaultSubobject<UMDEconomyComponent>("EconomyComponent");
}

ACharacter* UMDGameInstance::GetPlayerReference() const
{
    return PlayerReference;
}

void UMDGameInstance::SetPlayerReference(ACharacter *Character)
{
    PlayerReference = Character;
}

void UMDGameInstance::Init()
{
    Super::Init();

    PlayerReference = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

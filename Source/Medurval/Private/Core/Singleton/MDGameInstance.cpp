// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

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

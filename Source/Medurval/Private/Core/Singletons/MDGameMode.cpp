// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDGameMode.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/Components/Base/MDEconomyComponent.h"
#include "Core/Singletons/MDGameState.h"
#include "Core/Singletons/MDPlayerController.h"
#include "Core/Singletons/MDPlayerState.h"
#include "Kismet/GameplayStatics.h"

AMDGameMode::AMDGameMode()
{
	GameStateClass = AMDGameState::StaticClass();
	PlayerStateClass = AMDPlayerState::StaticClass();
	PlayerControllerClass = AMDPlayerController::StaticClass();

	Currency = CreateDefaultSubobject<UMDEconomyComponent>("EconomyComponent");
}

void AMDGameMode::StartPlay()
{
	Super::StartPlay();

	PlayerReference = Cast<AMDPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

AMDPlayerCharacter* AMDGameMode::GetPlayerReference() const
{
	return PlayerReference;
}

void AMDGameMode::SetPlayerReference(AMDPlayerCharacter* Character)
{
	PlayerReference = Character;
}

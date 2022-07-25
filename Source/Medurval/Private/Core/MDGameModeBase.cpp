// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/MDGameModeBase.h"

#include "Core/MDGameState.h"
#include "Core/MDPlayerController.h"
#include "Core/MDPlayerState.h"

AMDGameModeBase::AMDGameModeBase()
{
    GameStateClass = AMDGameState::StaticClass();
    PlayerStateClass = AMDPlayerState::StaticClass();
    PlayerControllerClass = AMDPlayerController::StaticClass();
}

void AMDGameModeBase::StartPlay()
{
    Super::StartPlay();
}

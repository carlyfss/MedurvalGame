// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDGameModeBase.h"

#include "Core/Singletons/MDGameState.h"
#include "Core/Singletons/MDPlayerController.h"
#include "Core/Singletons/MDPlayerState.h"

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

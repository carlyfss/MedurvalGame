// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Core/Actors/MDActor.h"

#include "Core/Constants/MDConstants.h"
#include "Core/Singletons/MDPlayerController.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMDActor::AMDActor()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;
    PrimaryActorTick.TickInterval = FMDConstants::TickInterval;

    USceneComponent *SceneComponent = CreateDefaultSubobject<USceneComponent>("Root");
    RootComponent = SceneComponent;
}

UMDGameInstance *AMDActor::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

AMDPlayerController *AMDActor::GetMDPlayerController() const
{
    return Cast<AMDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

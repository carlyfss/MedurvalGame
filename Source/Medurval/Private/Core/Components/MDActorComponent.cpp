// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Components/MDActorComponent.h"
#include "Core/Constants/MDConstants.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Core/Singletons/MDPlayerController.h"
#include "Kismet/GameplayStatics.h"

UMDActorComponent::UMDActorComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    PrimaryComponentTick.bStartWithTickEnabled = false;
    PrimaryComponentTick.TickInterval = FMDConstants::TickInterval;
}

UMDGameInstance* UMDActorComponent::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

AMDPlayerController* UMDActorComponent::GetMDPlayerController() const
{
    return Cast<AMDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

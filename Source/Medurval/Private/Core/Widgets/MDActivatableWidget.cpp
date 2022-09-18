// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Widgets/MDActivatableWidget.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Core/Singletons/MDPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UMDActivatableWidget::InitializeWidget()
{
}

UMDGameInstance* UMDActivatableWidget::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

AMDPlayerController* UMDActivatableWidget::GetMDPlayerController() const
{
    return Cast<AMDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

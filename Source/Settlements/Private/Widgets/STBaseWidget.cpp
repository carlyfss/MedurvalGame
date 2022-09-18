// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/STBaseWidget.h"

#include "Core/Singletons/MDPlayerController.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USTBaseWidget::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();
}

UMDGameInstance * USTBaseWidget::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

AMDPlayerController * USTBaseWidget::GetMDPlayerController() const
{
    return Cast<AMDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
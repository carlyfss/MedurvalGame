// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/SSBaseWidget.h"

#include "Core/MDPlayerController.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

void USSBaseWidget::NativeOnDeactivated()
{
    Super::NativeOnDeactivated();
}

UMDGameInstance * USSBaseWidget::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

AMDPlayerController * USSBaseWidget::GetMDPlayerController() const
{
    return Cast<AMDPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}
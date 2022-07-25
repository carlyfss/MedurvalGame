// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/MDPlayerController.h"

AMDPlayerController::AMDPlayerController()
{
}

void AMDPlayerController::SetInputModeGameOnly(bool InConsumeCaptureMouseDown)
{
    FInputModeGameOnly InputMode;
    InputMode.SetConsumeCaptureMouseDown(InConsumeCaptureMouseDown);
    SetInputMode(InputMode);
}

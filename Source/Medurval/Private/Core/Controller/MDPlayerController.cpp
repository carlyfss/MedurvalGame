// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Controller/MDPlayerController.h"

void AMDPlayerController::SetInputModeGameOnly(bool InConsumeCaptureMouseDown)
{
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(InConsumeCaptureMouseDown);
	SetInputMode(InputMode);
}

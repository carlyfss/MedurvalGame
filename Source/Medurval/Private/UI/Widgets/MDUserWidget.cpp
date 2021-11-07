// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "UI/Widgets/MDUserWidget.h"

void UMDUserWidget::SetPlayerReference(AMDBaseCharacter* PlayerRef)
{
	PlayerReference = PlayerRef;
}

AMDBaseCharacter* UMDUserWidget::GetPlayerReference() const
{
	return PlayerReference;
}

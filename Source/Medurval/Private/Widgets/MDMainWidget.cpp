// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Widgets/MDMainWidget.h"
#include "Characters/MDBaseCharacter.h"

void UMDMainWidget::SetPlayerReference(AMDBaseCharacter* PlayerRef)
{
    PlayerReference = PlayerRef;
}

AMDBaseCharacter* UMDMainWidget::GetPlayerReference() const
{
    return PlayerReference;
}
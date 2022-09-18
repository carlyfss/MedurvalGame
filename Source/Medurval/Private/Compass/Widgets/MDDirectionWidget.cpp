// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "Compass/Widgets/MDDirectionWidget.h"
#include "Components/TextBlock.h"

void UMDDirectionWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    const FString NameString = DirectionInfo.Name.ToString();

    const int ChopCount = NameString.Len() - 2;
    const FString ChoppedName = NameString.LeftChop(ChopCount).ToUpper();

    DirectionText->SetText(FText::FromString(ChoppedName));
}

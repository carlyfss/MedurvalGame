// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "UI/CDirectionWidget.h"

#include "Components/TextBlock.h"
#include "Internationalization/Text.h"

void UCDirectionWidget::NativePreConstruct()
{

    Super::NativePreConstruct();

    const FString NameString = DirectionInfo.Name.ToString();

    const int ChopCount = NameString.Len() - 2;
    const FString ChoppedName = NameString.LeftChop(ChopCount).ToUpper();

    DirectionText->SetText(FText::FromString(ChoppedName));
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/STBaseWidget.h"
#include "Structs/STBuildingTier.h"
#include "STTierIconTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTTierIconTooltipWidget : public USTBaseWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TierIconTooltipWidget")
    void SetupWidget(FSTBuildingTier TierData);
};

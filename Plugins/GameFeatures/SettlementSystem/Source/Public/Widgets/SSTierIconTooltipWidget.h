// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SSBaseWidget.h"
#include "Structs/SSBuildingTier.h"
#include "SSTierIconTooltipWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSTierIconTooltipWidget : public USSBaseWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TierIconTooltipWidget")
    void SetupWidget(FSSBuildingTier TierData);
};

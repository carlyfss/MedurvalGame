// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/STBaseWidget.h"
#include "Structs/STBuildingTier.h"
#include "STTierIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTS_API USTTierIconWidget : public USTBaseWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TierIconWidget")
    void SetupWidget(FSTBuildingTier TierData);
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SSBaseWidget.h"
#include "Structs/SSBuildingTier.h"
#include "SSTierIconWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSTierIconWidget : public USSBaseWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="TierIconWidget")
    void SetupWidget(FSSBuildingTier TierData);
};

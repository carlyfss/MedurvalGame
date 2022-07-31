// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSBasePopupWidget.h"
#include "SSClaimTerrainWidget.generated.h"

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSClaimTerrainWidget : public USSBasePopupWidget
{
    GENERATED_BODY()

public:
    virtual void UpdateWidget_Implementation() override;
    virtual void UpdateWidgetInfo_Implementation(ACharacter *CharacterReference, ASSTerrainActor *TerrainActor) override;
    virtual void StartUpdatingPosition_Implementation() override;
    virtual void StopUpdatingPosition_Implementation() override;
};

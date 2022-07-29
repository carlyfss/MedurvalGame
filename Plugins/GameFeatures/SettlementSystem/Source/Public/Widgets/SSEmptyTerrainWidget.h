// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "SSSettlementManagementWidget.h"
#include "Widgets/SSBaseWidget.h"
#include "SSEmptyTerrainWidget.generated.h"

class ASSTerrainActor;

/**
 * 
 */
UCLASS()
class SETTLEMENTSYSTEM_API USSEmptyTerrainWidget : public USSBaseWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category="ClaimTerrainWidget", meta=(AllowPrivateAccess=true))
    TObjectPtr<USSSettlementManagementWidget> SettlementManagementWidget;

public:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void UpdateWidgetInfo(ACharacter *CharacterReference, ASSTerrainActor *TerrainActor);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void UpdateWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void StartUpdatingPosition();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="ClaimTerrainWidget")
    void StopUpdatingPosition();
};

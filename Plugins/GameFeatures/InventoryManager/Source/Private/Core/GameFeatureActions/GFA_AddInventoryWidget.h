// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFeatureAction.h"
#include "GFA_AddInventoryWidget.generated.h"

class UBaseInventoryWidget;
/**
 * 
 */
UCLASS(meta=(DisplayName="AddInventoryWidget"))
class UGFA_AddInventoryWidget : public UGameFeatureAction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess=true))
	TSubclassOf<UBaseInventoryWidget> InventoryWidget = nullptr;

	virtual void OnGameFeatureLoading() override;
};

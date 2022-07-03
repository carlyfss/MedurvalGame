// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/FCDirectionInfo.h"
#include "CDirectionWidget.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class COMPASS_API UCDirectionWidget : public UUserWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "DirectionWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UTextBlock *DirectionText;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DirectionWidget", meta = (AllowPrivateAccess = true))
    FCDirectionInfo DirectionInfo;

    virtual void NativePreConstruct() override;
};
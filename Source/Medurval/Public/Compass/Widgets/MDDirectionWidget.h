// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Compass/Structs/MDDirectionInfo.h"
#include "Core/Widgets/MDActivatableWidget.h"
#include "MDDirectionWidget.generated.h"

class UTextBlock;
/**
 *
 */
UCLASS()
class MEDURVAL_API UMDDirectionWidget : public UMDActivatableWidget
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, Category = "DirectionWidget", meta = (AllowPrivateAccess = true, BindWidget))
    UTextBlock *DirectionText;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DirectionWidget", meta = (AllowPrivateAccess = true))
    FMDDirectionInfo DirectionInfo;

    virtual void NativePreConstruct() override;
};
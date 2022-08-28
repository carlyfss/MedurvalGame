// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Items/IVBaseItemDA.h"
#include "IVResourceItemDA.generated.h"

/**
 * 
 */
UCLASS(meta=(DisplayName="ResourceItemDA"))
class INVENTORY_API UIVResourceItemDA : public UIVBaseItemDA
{
    GENERATED_BODY()
    
public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

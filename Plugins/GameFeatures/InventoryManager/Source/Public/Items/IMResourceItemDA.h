// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Items/IMBaseItemDA.h"
#include "IMResourceItemDA.generated.h"

/**
 * 
 */
UCLASS()
class INVENTORYMANAGER_API UIMResourceItemDA : public UIMBaseItemDA
{
    GENERATED_BODY()
    
public:
    virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};

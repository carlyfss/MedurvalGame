// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MDGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDGameInstance final : public UGameInstance
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category="MDGameInstance", meta=(AllowPrivateAccess=true))
    TObjectPtr<ACharacter> PlayerReference;
    
public:
	FStreamableManager AssetLoader;

    UFUNCTION(BlueprintCallable, Category="MDGameInstance")
    ACharacter* GetPlayerReference() const;

    void SetPlayerReference(ACharacter* Character);

    virtual void Init() override;
};

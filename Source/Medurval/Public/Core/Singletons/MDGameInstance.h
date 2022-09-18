// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
#include "MDGameInstance.generated.h"

class UMDEconomyComponent;
/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDGameInstance final : public UGameInstance
{
	GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDEconomyComponent> Currency;

    UPROPERTY(BlueprintReadOnly, Category="MDGameInstance", meta=(AllowPrivateAccess=true))
    TObjectPtr<ACharacter> PlayerReference;
    
public:
    UMDGameInstance();
    
	FStreamableManager AssetLoader;

    UFUNCTION(BlueprintCallable, Category="MDGameInstance")
    ACharacter* GetPlayerReference() const;

    void SetPlayerReference(ACharacter* Character);

    virtual void Init() override;
};

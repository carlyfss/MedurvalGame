// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "CommonUserWidget.h"
#include "MDMainWidget.generated.h"

class AMDBaseCharacter;

/**
 * 
 */
UCLASS()
class MEDURVAL_API UMDMainWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

    UPROPERTY(BlueprintSetter=SetPlayerReference, BlueprintGetter=GetPlayerReference, Category="References")
    TObjectPtr<AMDBaseCharacter> PlayerReference = nullptr;

public:

    UFUNCTION(BlueprintCallable, Category="Base|Setters")
    void SetPlayerReference(AMDBaseCharacter* PlayerRef);

    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Base|Getters")
    AMDBaseCharacter* GetPlayerReference() const;
};

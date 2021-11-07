// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MDUserWidget.generated.h"

class AMDBaseCharacter;
/**
 * 
 */
UCLASS()
class UMDUserWidget : public UUserWidget
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

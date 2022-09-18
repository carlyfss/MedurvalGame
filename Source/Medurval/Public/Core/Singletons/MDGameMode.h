// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MDGameMode.generated.h"

class AMDPlayerCharacter;
class UMDEconomyComponent;
/**
 * 
 */
UCLASS()
class MEDURVAL_API AMDGameMode final : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDEconomyComponent> Currency;

	UPROPERTY(BlueprintReadOnly, Category="MDGameInstance", meta=(AllowPrivateAccess=true))
	TObjectPtr<AMDPlayerCharacter> PlayerReference;

public:
	AMDGameMode();
	virtual ~AMDGameMode() = default;

	/** Called before begin play */
	virtual void StartPlay() override;

	AMDPlayerCharacter* GetPlayerReference() const;

	void SetPlayerReference(AMDPlayerCharacter* Character);
};

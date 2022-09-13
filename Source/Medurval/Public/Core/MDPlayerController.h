// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameFramework/PlayerController.h"
#include "Widgets/MDMainWidget.h"
#include "MDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API AMDPlayerController : public APlayerController
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSubclassOf<UCommonActivatableWidget> BaseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UCommonActivatableWidget> CharacterWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UCommonActivatableWidget> SettlementWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UCommonActivatableWidget> BuildingsListWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCommonActivatableWidget> BaseWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCommonActivatableWidget> CharacterWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCommonActivatableWidget> SettlementWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    bool bIsSettlementView = false;

    TSharedPtr<FStreamableHandle> WidgetLoadHandle;

protected:
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void CompleteConfiguration();
    
public:
    AMDPlayerController();
    virtual ~AMDPlayerController() = default;

    void LoadWidgets();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void PushSettlementWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void PushCharacterWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void OpenBuildingsList(AActor *TerrainActor, bool bIsOnSettlementView);

    void SetSettlementView(bool bIsOnSettlementView);

    

    UFUNCTION(BlueprintCallable, Category="MDPlayerController")
    UCommonActivatableWidget *GetSettlementWidget();

    virtual void BeginPlay() override;
};

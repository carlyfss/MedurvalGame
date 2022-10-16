// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "Core/Widgets/MDGameBaseWidget.h"
#include "Core/Widgets/MDGameMenuWidget.h"
#include "GameFramework/PlayerController.h"
#include "MDPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MEDURVAL_API AMDPlayerController : public APlayerController
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSubclassOf<UMDGameBaseWidget> BaseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UMDGameMenuWidget> GameMenuWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UMDActivatableWidget> CharacterWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UMDActivatableWidget> SettlementWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<UMDActivatableWidget> BuildingsListWidgetClass;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDGameBaseWidget> BaseWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDGameMenuWidget> GameMenuWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDActivatableWidget> CharacterWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDActivatableWidget> SettlementWidget;

    UPROPERTY(BlueprintReadWrite, Category="MDPlayerController", meta=(AllowPrivateAccess=true))
    bool bIsSettlementView = false;

    TSharedPtr<FStreamableHandle> WidgetLoadHandle;

protected:
    bool IsClassesLoaded();
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void SetupWidgetConfiguration();
    
public:
    AMDPlayerController();
    virtual ~AMDPlayerController() = default;

    void LoadWidgets();

    void OnWidgetsLoaded();

    UFUNCTION(BlueprintCallable, Category="MDPlayerController")
    UMDActivatableWidget* PushWidget(TSubclassOf<UMDActivatableWidget> WidgetClass);

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void PushGameMenuWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void PushSettlementWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void PushCharacterWidget();

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="MDPlayerController")
    void OpenBuildingsList(AActor *TerrainActor, bool bIsOnSettlementView);

    void SetSettlementView(bool bIsOnSettlementView);
    
    UFUNCTION(BlueprintCallable, Category="MDPlayerController")
    UMDActivatableWidget* GetSettlementWidget();

    virtual void BeginPlay() override;
};

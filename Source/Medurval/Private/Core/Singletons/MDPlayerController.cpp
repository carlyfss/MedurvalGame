// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDPlayerController.h"

#include "Core/AssetManager/MedurvalAssetManager.h"

AMDPlayerController::AMDPlayerController()
{
}

void AMDPlayerController::LoadWidgets()
{
    FStreamableManager &StreamableManager = UAssetManager::GetStreamableManager();

    TArray<FSoftObjectPath> Objects;

    Objects.Add(CharacterWidgetClass.ToSoftObjectPath());
    Objects.Add(SettlementWidgetClass.ToSoftObjectPath());
    Objects.Add(BuildingsListWidgetClass.ToSoftObjectPath());
    Objects.Add(GameMenuWidgetClass.ToSoftObjectPath());

    WidgetLoadHandle = StreamableManager.RequestAsyncLoad(Objects);
}

UMDActivatableWidget* AMDPlayerController::PushWidget(TSubclassOf<UMDActivatableWidget> WidgetClass)
{
    UMDActivatableWidget* Widget = nullptr;

    if (BaseWidget)
    {
        Widget = BaseWidget->PushPrompt(WidgetClass);
    }

    return Widget;
}

void AMDPlayerController::SetSettlementView(bool bIsOnSettlementView)
{
    bIsSettlementView = bIsOnSettlementView;
}

UMDActivatableWidget* AMDPlayerController::GetSettlementWidget()
{
    return SettlementWidget;
}

void AMDPlayerController::BeginPlay()
{
    Super::BeginPlay();

    LoadWidgets();

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &AMDPlayerController::CompleteConfiguration);

    if (WidgetLoadHandle->HasLoadCompleted())
    {
        CompleteConfiguration();
    }
    else
    {
        WidgetLoadHandle->BindCompleteDelegate(Delegate);
    }
    
}


// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDPlayerController.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
#include "Core/AssetManager/MedurvalAssetManager.h"

bool AMDPlayerController::IsClassesLoaded()
{
    bool IsAllClassesLoaded = false;

    if (SettlementWidgetClass.Get())
    {
        IsAllClassesLoaded = true;
    }

    if (BuildingsListWidgetClass.Get())
    {
        IsAllClassesLoaded = true;
    }

    if (GameMenuWidgetClass.Get())
    {
        IsAllClassesLoaded = true;
    }

    if (CharacterWidgetClass.Get())
    {
        IsAllClassesLoaded = true;
    }

    return IsAllClassesLoaded;
}

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

    FStreamableDelegate Delegate =
        FStreamableDelegate::CreateUObject(this, &AMDPlayerController::OnWidgetsLoaded);
    WidgetLoadHandle = StreamableManager.RequestAsyncLoad(Objects, Delegate);
}

void AMDPlayerController::OnWidgetsLoaded()
{
    UE_LOG(LogTemp, Warning, TEXT("Setup widget configuration on Player Controller after load!"))
    SetupWidgetConfiguration();
    
    AMDPlayerCharacter* PlayerCharacter = Cast<AMDPlayerCharacter>(GetCharacter());

    if (PlayerCharacter)
    {
        TArray<UActorComponent*> PlayerComponents;
        PlayerCharacter->GetComponents(PlayerComponents);

        for (UActorComponent* Component : PlayerComponents)
        {
            UMDInventoryComponent* Inventory = Cast<UMDInventoryComponent>(Component);

            if (Inventory && GameMenuWidget)
            {
                GameMenuWidget->ConfigureInventoryWidget(Inventory);
                UE_LOG(LogTemp, Warning, TEXT("Inventory is being configured on Player Controller after load!"))
            }    
        }
    }
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
}


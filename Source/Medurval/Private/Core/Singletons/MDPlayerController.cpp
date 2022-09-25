// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Singletons/MDPlayerController.h"

#include "Core/Actors/Characters/MDPlayerCharacter.h"
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

    FStreamableDelegate Delegate =
        FStreamableDelegate::CreateUObject(this, &AMDPlayerController::OnWidgetsLoaded);
    WidgetLoadHandle = StreamableManager.RequestAsyncLoad(Objects, Delegate);
}

void AMDPlayerController::OnWidgetsLoaded()
{
    AMDPlayerCharacter* PlayerCharacter = Cast<AMDPlayerCharacter>(GetCharacter());

    if (PlayerCharacter)
    {
        TSubclassOf<UMDInventoryComponent> InventoryClass;
        UMDInventoryComponent* Inventory = Cast<UMDInventoryComponent>(
            PlayerCharacter->GetComponentByClass(InventoryClass));

        if (Inventory && GameMenuWidget)
        {
            GameMenuWidget->ConfigureInventoryWidget(Inventory);
            UE_LOG(LogTemp, Warning, TEXT("Inventory is being configured on Player Controller!"))
        }
    }

    UE_LOG(LogTemp, Warning, TEXT("Finishing widget configuration on Player Controller!"))
    CompleteConfiguration();
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


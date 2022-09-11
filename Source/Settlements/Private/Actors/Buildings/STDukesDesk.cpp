// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Buildings/STDukesDesk.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/STSettlementComponent.h"
#include "Core/MDPlayerController.h"
#include "Core/Components/MDBoxComponent.h"
#include "Core/Components/MDSphereComponent.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Medurval/Private/Characters/MDBaseCharacter.h"
#include "Pawns/STEaglesViewPawn.h"

ASTDukesDesk::ASTDukesDesk()
{
    SettlementComponent = CreateDefaultSubobject<USTSettlementComponent>("SettlementComponent");
    
    SettlementSizeCollision = CreateDefaultSubobject<UMDSphereComponent>("SettlementSizeCollision");
    SettlementSizeCollision->SetupAttachment(RootComponent);
    SettlementSizeCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    SettlementSizeCollision->SetCollisionObjectType(ECC_GameTraceChannel5);
    SettlementSizeCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SettlementSizeCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);

    SettlementRangeCollision = CreateDefaultSubobject<UMDBoxComponent>("SettlementRangeCollision");
    SettlementRangeCollision->SetupAttachment(RootComponent);
    SettlementRangeCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    SettlementRangeCollision->SetCollisionObjectType(ECC_GameTraceChannel5);
    SettlementRangeCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SettlementRangeCollision->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Overlap);

    DeskCollision = CreateDefaultSubobject<UMDBoxComponent>("DeskCollision");
    DeskCollision->SetupAttachment(RootComponent);
    DeskCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    DeskCollision->SetCollisionObjectType(ECC_GameTraceChannel2);
    DeskCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DeskCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void ASTDukesDesk::UpdateSettlementRangeAndSize()
{
    if (EaglesViewActor)
    {
        float Range = SettlementComponent->GetSettlementRange();
        float Altitude = EaglesViewActor->GetMaxZoomDistance();
        SettlementRangeCollision->SetBoxExtent(FVector(Range, Range, Altitude));
        SettlementSizeCollision->SetSphereRadius(SettlementComponent->GetSettlementSize());
    }
}

void ASTDukesDesk::BeginPlay()
{
    Super::BeginPlay();

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASTDukesDesk::CreateEaglesViewActor);
    LoadClass(EaglesViewActorClass, Delegate);

    SpawnSettlementSizeDecal();
}

void ASTDukesDesk::CreateEaglesViewActor()
{
    if (EaglesViewActorClass.Get())
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        FVector Location = this->GetActorLocation() + 50;
        FRotator Rotation = this->GetActorRotation();
        FRotator NewRotation = FRotator(Rotation.Pitch, Rotation.Yaw + 180, Rotation.Roll);
        EaglesViewActor = GetWorld()->SpawnActor<ASTEaglesViewPawn>(EaglesViewActorClass.Get(), Location, NewRotation, SpawnParameters);
        EaglesViewActor->DisableLineTrace();

        FinishSettlementConfiguration();
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("EaglesViewActor class not loaded!"));
    }
}

void ASTDukesDesk::RegisterSettlement()
{
    if (SettlementComponent && EaglesViewActor)
    {
        SettlementComponent->SetSettlementOwner(GetMDGameInstance()->GetPlayerReference());

        GetSettlementSubsystem()->RegisterNewSettlement(SettlementComponent);

        USTSettlementComponent *Settlement = GetSettlementSubsystem()->GetSettlementByOwner(GetMDGameInstance()->GetPlayerReference());

        if (Settlement)
        {
            Settlement->GetEconomy()->SetStartingTreasury(StartingTreasury);
        }
    }
}

void ASTDukesDesk::FinishSettlementConfiguration()
{
    RegisterSettlement();
    UpdateSettlementRangeAndSize();
}

void ASTDukesDesk::PossessEaglesViewActor()
{
    if (EaglesViewActor)
    {
        AMDPlayerController *Controller = GetMDPlayerController();
        Controller->Possess(EaglesViewActor);
        Controller->SetShowMouseCursor(true);

        EaglesViewActor->EnableLineTrace();

        AMDBaseCharacter *PlayerCharacter = Cast<AMDBaseCharacter>(GetMDGameInstance()->GetPlayerReference());

        if (PlayerCharacter)
        {
            PlayerCharacter->DisableLineTrace();
        }

        UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(Controller);

        Controller->PushSettlementWidget();
        Controller->SetSettlementView(true);
        EaglesViewActor->SetSettlementWidget(Controller->GetSettlementWidget());
        ShowTerrainsInRange();
    }
}

void ASTDukesDesk::PossessCharacterActor()
{
    AMDPlayerController *Controller = GetMDPlayerController();
    Controller->SetShowMouseCursor(false);

    EaglesViewActor->DisableLineTrace();

    AMDBaseCharacter *PlayerCharacter = Cast<AMDBaseCharacter>(GetMDGameInstance()->GetPlayerReference());

    if (PlayerCharacter)
    {
        Controller->Possess(PlayerCharacter);
        PlayerCharacter->EnableLineTrace();
    }

    UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);

    Controller->PushCharacterWidget();
    Controller->SetSettlementView(false);
    HideTerrainsInRange();
}

void ASTDukesDesk::GetAndShowTerrainsInSettlementRange()
{
    OverlappedTerrains.Empty();

    TArray<AActor *> OverlappingActors;
    TSubclassOf<ASTTerrainActor> TerrainClass;
    SettlementRangeCollision->GetOverlappingActors(OverlappingActors, TerrainClass);

    if (OverlappingActors.Num() > 0)
    {
        for (AActor *Actor : OverlappingActors)
        {
            ASTTerrainActor *Terrain = Cast<ASTTerrainActor>(Actor);

            if (Terrain)
            {
                OverlappedTerrains.Add(Terrain);
                Terrain->ShowTarget();
            }
        }
    }
}

void ASTDukesDesk::ShowTerrainsInRange()
{
    if (SettlementSizeDecal)
    {
        SettlementSizeDecal->SetVisibility(true);
        SetClaimableTerrainsInSettlementSize();
        GetAndShowTerrainsInSettlementRange();
    }
}

void ASTDukesDesk::HideTerrainsInRange()
{
    SettlementSizeDecal->SetVisibility(false);

    if (OverlappedTerrains.Num() > 0)
    {
        for (ASTTerrainActor *Terrain : OverlappedTerrains)
        {
            Terrain->HideTarget();
        }
    }
}

void ASTDukesDesk::SetClaimableTerrainsInSettlementSize()
{
    TArray<AActor *> OverlappingActors;
    TSubclassOf<ASTTerrainActor> TerrainClass;
    SettlementSizeCollision->GetOverlappingActors(OverlappingActors, TerrainClass);

    if (OverlappingActors.Num() > 0)
    {
        for (AActor *Actor : OverlappingActors)
        {
            ASTTerrainActor *Terrain = Cast<ASTTerrainActor>(Actor);

            if (Terrain)
            {
                Terrain->SetIsClaimable(true);
            }
        }
    }
}

void ASTDukesDesk::SpawnSettlementSizeDecal()
{
    const float SettlementSize = SettlementComponent->GetSettlementSize();
    const FVector TargetSize = FVector(200, SettlementSize, SettlementSize);
    const FVector Location = this->GetActorLocation();
    const FRotator Rotation = FRotator(90, this->GetActorRotation().Yaw, this->GetActorRotation().Roll);
    SettlementSizeDecal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), SettlementSizeDecalMaterial, TargetSize, Location, Rotation);
    SettlementSizeDecal->SetVisibility(false);
    SettlementSizeDecal->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

    SettlementSizeDecalMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SettlementSizeDecalMaterial);

    SettlementSizeDecal->SetDecalMaterial(SettlementSizeDecalMaterialInstance);
    SettlementSizeDecal->SetWorldRotation(FRotator(90, this->GetActorRotation().Yaw, 0));
}



// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Buildings/STDukesDesk.h"

#include "Components/STSettlementComponent.h"
#include "Core/Components/MDBoxComponent.h"
#include "Core/Components/MDSphereComponent.h"
#include "Core/Singleton/MDGameInstance.h"
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
    DeskCollision->SetCollisionResponseToChannel(ECC_Visibility, ECR_Overlap);
}

void ASTDukesDesk::UpdateSettlementRangeAndSize()
{
    float Range = SettlementComponent->GetSettlementRange();
    SettlementRangeCollision->SetBoxExtent(FVector(Range, Range, EaglesViewActor->GetMaxZoomDistance()));
    SettlementSizeCollision->SetSphereRadius(SettlementComponent->GetSettlementSize());
}

void ASTDukesDesk::BeginPlay()
{
    Super::BeginPlay();

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASTDukesDesk::CreateEaglesViewActor);
    LoadClass(EaglesViewActorClass, Delegate);

    RegisterSettlement();
}

void ASTDukesDesk::CreateEaglesViewActor()
{
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    FVector Location = this->GetActorLocation() + 50;
    FRotator Rotation = this->GetActorRotation();
    FRotator NewRotation = FRotator(Rotation.Pitch, Rotation.Yaw + 180, Rotation.Roll);
    EaglesViewActor = GetWorld()->SpawnActor<ASTEaglesViewPawn>(EaglesViewActorClass.Get(), Location, NewRotation, SpawnParameters);
    EaglesViewActor->DisableLineTrace();
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

            UpdateSettlementRangeAndSize();
        }
    }
}



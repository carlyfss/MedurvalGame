// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/STTerrainActor.h"

#include "Components/DecalComponent.h"
#include "Components/STSettlementComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Structs/STTerrainConstants.h"
#include "Subsystems/STSettlementSubsystem.h"

void ASTTerrainActor::CompleteConstruction()
{
    if (!ConstructedBuilding)
        return;

    ConstructedBuilding->OnConstructionCompleted();
}

void ASTTerrainActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);

    float NewWidth;
    float NewLength;

    SnapSize(NewWidth, NewLength);
    const FVector NewCollisionSize = CalculateTerrainSize(NewWidth, NewLength);

    Collision->SetBoxExtent(NewCollisionSize);
}

void ASTTerrainActor::BeginPlay()
{
    Super::BeginPlay();

    SnapSize(Width, Length);
    const FVector TerrainSize = CalculateTerrainSize(Width, Length);
    const FVector TargetSize = FVector(FSTTerrainConstants::DefaultTargetHeight, TerrainSize.Y, TerrainSize.X);
    const FVector Location = this->GetActorLocation();
    const FRotator Rotation = FRotator(0, this->GetActorRotation().Yaw, 90);
    Target = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DefaultTargetMaterial, TargetSize, Location, Rotation);
    Target->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

    TargetMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DefaultTargetMaterial, FSTTerrainConstants::TargetColorParameterName);

    SetTargetColor(FSTTerrainConstants::DefaultUnclaimedTargetColor);
    Target->SetDecalMaterial(TargetMaterialInstance);

    Target->SetWorldRotation(FRotator(90, this->GetActorRotation().Yaw, 0));

    LoadAssignedBuilding();
}

void ASTTerrainActor::OnInteract_Implementation(AActor *InstigatorActor)
{
    IMDInteractableInterface::OnInteract_Implementation(InstigatorActor);
}

void ASTTerrainActor::OnStartFocus_Implementation()
{
    IMDInteractableInterface::OnStartFocus_Implementation();
    OnTerrainStartFocus();
}

void ASTTerrainActor::OnEndFocus_Implementation()
{
    IMDInteractableInterface::OnEndFocus_Implementation();
    OnTerrainEndFocus();
}


ASTTerrainActor::ASTTerrainActor()
{
    Collision = CreateDefaultSubobject<UCBBoxComponent>("Collision");

    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionObjectType(ECC_GameTraceChannel4);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);

    RootComponent = Collision;
}

void ASTTerrainActor::LoadAssignedBuilding()
{
    FStreamableManager &StreamableManager = UMedurvalAssetManager::GetStreamableManager();

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASTTerrainActor::OnAssignedBuildingLoaded);
    StreamableManager.RequestAsyncLoad(AssignedBuilding.ToSoftObjectPath(), Delegate);
}

void ASTTerrainActor::OnAssignedBuildingLoaded()
{
    if (!AssignedBuilding.Get())
        return;

    const FVector TerrainLocation = this->GetActorLocation();
    const FRotator TerrainRotation = this->GetActorRotation();

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ConstructedBuilding = GetWorld()->SpawnActor<ASTBuildingActor>(AssignedBuilding.Get(), TerrainLocation, TerrainRotation, SpawnParameters);
    ConstructedBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

    OnAssignedBuildingLoadCompleted.Broadcast();
    StartConstruction_Implementation();
}

void ASTTerrainActor::UpdateWidthLengthValues()
{
    if (Size == ESTTerrainSize::Small)
    {
        MaxLengthWidth = FSTTerrainConstants::MaxSizeSmall * FSTTerrainConstants::UnitsPerMeter;
        MinLengthWidth = FSTTerrainConstants::MinSizeSmall * FSTTerrainConstants::UnitsPerMeter;
    }

    if (Size == ESTTerrainSize::Medium)
    {
        MaxLengthWidth = FSTTerrainConstants::MaxSizeMedium * FSTTerrainConstants::UnitsPerMeter;
        MinLengthWidth = FSTTerrainConstants::MinSizeMedium * FSTTerrainConstants::UnitsPerMeter;
    }

    if (Size == ESTTerrainSize::Large)
    {
        MaxLengthWidth = FSTTerrainConstants::MaxSizeLarge * FSTTerrainConstants::UnitsPerMeter;
        MinLengthWidth = FSTTerrainConstants::MinSizeLarge * FSTTerrainConstants::UnitsPerMeter;
    }
}

void ASTTerrainActor::SetTargetColor(FLinearColor NewColor)
{
    if (Status == ESTTerrainStatus::Unclaimed && NewColor == FSTTerrainConstants::DefaultTargetColor)
    {
        TargetMaterialInstance->SetVectorParameterValue(FSTTerrainConstants::TargetColorParameterName, FSTTerrainConstants::DefaultUnclaimedTargetColor);
        return;
    }

    TargetMaterialInstance->SetVectorParameterValue(FSTTerrainConstants::TargetColorParameterName, NewColor);
}

FVector ASTTerrainActor::CalculateTerrainSize(float NewWidth, float NewLength)
{
    UpdateWidthLengthValues();

    const float ClampedWidth = FMath::Clamp(NewWidth, MinLengthWidth, MaxLengthWidth);
    const float ClampedLength = FMath::Clamp(NewLength, MinLengthWidth, MaxLengthWidth);

    const FVector NewSize = FVector(ClampedWidth, ClampedLength, FSTTerrainConstants::DefaultTargetHeight);

    return NewSize;
}

void ASTTerrainActor::SnapSize(float &NewWidth, float &NewLength) const
{
    const float WidthRest = FMath::TruncToInt(Width) % FMath::TruncToInt(FSTTerrainConstants::UnitsPerMeter);
    const float LengthRest = FMath::TruncToInt(Length) % FMath::TruncToInt(FSTTerrainConstants::UnitsPerMeter);

    NewWidth = FMath::TruncToInt(Width) - WidthRest;
    NewLength = FMath::TruncToInt(Length) - LengthRest;
}

bool ASTTerrainActor::Claim(ACharacter *OwnerReference, ESTCivilizationType CivilizationType)
{
    const UGameInstance *GameInstance = GetWorld()->GetGameInstance();

    if (!GameInstance)
        return false;

    USTSettlementSubsystem *Subsystem = GameInstance->GetSubsystem<USTSettlementSubsystem>();

    if (!Subsystem)
        return false;

    USTSettlementComponent *Settlement = Subsystem->GetSettlementByOwner(OwnerReference);

    if (!Settlement)
        return false;

    if (!Settlement->AddNewTerrain(this))
        return false;

    Settlement->GetEconomy()->RemoveFromTreasury(ClaimFee);
    Civilization = CivilizationType;
    Status = ESTTerrainStatus::Claimed;
    OnClaimed.Broadcast(this);
    return true;
}

bool ASTTerrainActor::IsUnclaimed()
{
    return Status == ESTTerrainStatus::Unclaimed;
}

void ASTTerrainActor::ShowTarget()
{
    Target->SetVisibility(true);
}

void ASTTerrainActor::HideTarget()
{
    Target->SetVisibility(false);
}

void ASTTerrainActor::SelectTarget()
{
    SetTargetColor(FSTTerrainConstants::DefaultSelectedTargetColor);
    OnSelected.Broadcast(this);
    bIsSelected = true;
}

void ASTTerrainActor::DeselectTarget()
{
    SetTargetColor(FSTTerrainConstants::DefaultTargetColor);
    bIsSelected = false;
}

void ASTTerrainActor::SetAssignedBuilding(TSoftClassPtr<ASTBuildingActor> Building)
{
    AssignedBuilding = Building;
}

void ASTTerrainActor::StartConstruction_Implementation()
{
    if (!ConstructedBuilding)
        return;

    OnStartConstruction.Broadcast(this);
    bIsUnderConstruction = true;
    ConstructedBuilding->OnBeginConstruction();
    Status = ESTTerrainStatus::Constructed;
}

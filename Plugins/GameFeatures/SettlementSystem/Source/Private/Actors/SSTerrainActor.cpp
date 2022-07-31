// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/SSTerrainActor.h"

#include "Components/DecalComponent.h"
#include "Components/SSSettlementComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Structs/SSTerrainConstants.h"
#include "Subsystems/SSSettlementSubsystem.h"

void ASSTerrainActor::OnConstruction(const FTransform &Transform)
{
    Super::OnConstruction(Transform);

    float NewWidth;
    float NewLength;

    SnapSize(NewWidth, NewLength);
    const FVector NewCollisionSize = CalculateTerrainSize(NewWidth, NewLength);

    Collision->SetBoxExtent(NewCollisionSize);
}

void ASSTerrainActor::BeginPlay()
{
    Super::BeginPlay();

    LoadAssignedBuilding();

    SnapSize(Width, Length);
    const FVector TerrainSize = CalculateTerrainSize(Width, Length);
    const FVector TargetSize = FVector(FSSTerrainConstants::DefaultTargetHeight, TerrainSize.Y, TerrainSize.X);
    const FVector Location = this->GetActorLocation();
    const FRotator Rotation = FRotator(0, this->GetActorRotation().Yaw, 90);
    Target = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DefaultTargetMaterial, TargetSize, Location, Rotation);
    Target->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

    TargetMaterialInstance = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), DefaultTargetMaterial, FSSTerrainConstants::TargetColorParameterName);

    SetTargetColor(FSSTerrainConstants::DefaultUnclaimedTargetColor);
    Target->SetDecalMaterial(TargetMaterialInstance);

    Target->SetWorldRotation(FRotator(90, this->GetActorRotation().Yaw, 0));
}


ASSTerrainActor::ASSTerrainActor()
{
    Collision = CreateDefaultSubobject<UCBBoxComponent>("Collision");

    Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Collision->SetCollisionObjectType(ECC_GameTraceChannel4);
    Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
    Collision->SetCollisionResponseToChannel(ECC_GameTraceChannel4, ECR_Block);

    RootComponent = Collision;
}

void ASSTerrainActor::LoadAssignedBuilding()
{
    FStreamableManager &StreamableManager = UMedurvalAssetManager::GetStreamableManager();

    TArray<FName> BundlesToLoad;
    BundlesToLoad.Add(UMedurvalAssetManager::UIBundle);

    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASSTerrainActor::OnAssignedBuildingLoaded);
    StreamableManager.RequestAsyncLoad(AssignedBuilding.ToSoftObjectPath(), Delegate);
}

void ASSTerrainActor::OnAssignedBuildingLoaded()
{
    if (!AssignedBuilding.Get())
        return;

    const FVector TerrainLocation = this->GetActorLocation();
    const FRotator TerrainRotation = this->GetActorRotation();

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    ConstructedBuilding = GetWorld()->SpawnActor<ASSBuildingActor>(AssignedBuilding.Get(), TerrainLocation, TerrainRotation, SpawnParameters);
    ConstructedBuilding->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetIncludingScale);

    OnAssignedBuildingLoadCompleted.Broadcast();
    StartConstruction_Implementation();
}

void ASSTerrainActor::UpdateWidthLengthValues()
{
    if (Size == ESSTerrainSize::Small)
    {
        MaxLengthWidth = FSSTerrainConstants::MaxSizeSmall * FSSTerrainConstants::UnitsPerMeter;
        MinLengthWidth = FSSTerrainConstants::MinSizeSmall * FSSTerrainConstants::UnitsPerMeter;
    }

    if (Size == ESSTerrainSize::Medium)
    {
        MaxLengthWidth = FSSTerrainConstants::MaxSizeMedium * FSSTerrainConstants::UnitsPerMeter;
        MinLengthWidth = FSSTerrainConstants::MinSizeMedium * FSSTerrainConstants::UnitsPerMeter;
    }

    if (Size == ESSTerrainSize::Large)
    {
        MaxLengthWidth = FSSTerrainConstants::MaxSizeLarge * FSSTerrainConstants::UnitsPerMeter;
        MinLengthWidth = FSSTerrainConstants::MinSizeLarge * FSSTerrainConstants::UnitsPerMeter;
    }
}

void ASSTerrainActor::SetTargetColor(FLinearColor NewColor)
{
    if (Status == ESSTerrainStatus::Unclaimed && NewColor == FSSTerrainConstants::DefaultTargetColor)
    {
        TargetMaterialInstance->SetVectorParameterValue(FSSTerrainConstants::TargetColorParameterName, FSSTerrainConstants::DefaultUnclaimedTargetColor);
        return;
    }

    TargetMaterialInstance->SetVectorParameterValue(FSSTerrainConstants::TargetColorParameterName, NewColor);
}

FVector ASSTerrainActor::CalculateTerrainSize(float NewWidth, float NewLength)
{
    UpdateWidthLengthValues();

    const float ClampedWidth = FMath::Clamp(NewWidth, MinLengthWidth, MaxLengthWidth);
    const float ClampedLength = FMath::Clamp(NewLength, MinLengthWidth, MaxLengthWidth);

    const FVector NewSize = FVector(ClampedWidth, ClampedLength, FSSTerrainConstants::DefaultTargetHeight);

    return NewSize;
}

void ASSTerrainActor::SnapSize(float &NewWidth, float &NewLength) const
{
    const float WidthRest = FMath::TruncToInt(Width) % FMath::TruncToInt(FSSTerrainConstants::UnitsPerMeter);
    const float LengthRest = FMath::TruncToInt(Length) % FMath::TruncToInt(FSSTerrainConstants::UnitsPerMeter);

    NewWidth = FMath::TruncToInt(Width) - WidthRest;
    NewLength = FMath::TruncToInt(Length) - LengthRest;
}

bool ASSTerrainActor::Claim(ACharacter *OwnerReference)
{
    const UGameInstance *GameInstance = GetWorld()->GetGameInstance();

    if (!GameInstance)
        return false;

    USSSettlementSubsystem *Subsystem = GameInstance->GetSubsystem<USSSettlementSubsystem>();

    if (!Subsystem)
        return false;

    USSSettlementComponent *Settlement = Subsystem->GetSettlementByOwner(OwnerReference);

    if (!Settlement)
        return false;

    if (!Settlement->AddNewTerrain(this))
        return false;

    Settlement->GetEconomy()->RemoveFromTreasury(ClaimFee);
    Status = ESSTerrainStatus::Claimed;
    return true;
}

bool ASSTerrainActor::IsUnclaimed()
{
    return Status == ESSTerrainStatus::Unclaimed;
}

void ASSTerrainActor::ShowTarget()
{
    Target->SetVisibility(true);
}

void ASSTerrainActor::HideTarget()
{
    Target->SetVisibility(false);
}

void ASSTerrainActor::SelectTarget()
{
    SetTargetColor(FSSTerrainConstants::DefaultSelectedTargetColor);
    OnSelected.Broadcast(this);
    bIsSelected = true;
}

void ASSTerrainActor::DeselectTarget()
{
    SetTargetColor(FSSTerrainConstants::DefaultTargetColor);
    bIsSelected = false;
}

void ASSTerrainActor::SetAssignedBuilding(TSoftClassPtr<ASSBuildingActor> Building)
{
    AssignedBuilding = Building;
}

void ASSTerrainActor::StartConstruction_Implementation()
{
    if (!ConstructedBuilding)
        return;

    OnStartConstruction.Broadcast(this);
    bIsUnderConstruction = true;
    ConstructedBuilding->OnBeginConstruction_Implementation();
    ConstructedBuilding->OnBeginConstruction();
    Status = ESSTerrainStatus::Constructed;
    SetTargetColor(FSSTerrainConstants::DefaultTargetColor);
}

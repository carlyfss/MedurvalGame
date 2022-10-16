// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Actors/Characters/MDEnhancedCharacter.h"

#include "Core/Singletons/MDGameInstance.h"
#include "Core/Singletons/MDPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Inventory/Items/MDEquipmentDataAsset.h"
#include "Kismet/GameplayStatics.h"

void AMDEnhancedCharacter::SetupEquipmentSlots()
{
	if (GetMesh())
	{
		HelmetSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		HelmetSlot->SetAnimClass(GetMesh()->GetAnimClass());

		ChestSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ChestSlot->SetAnimClass(GetMesh()->GetAnimClass());

		GlovesSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		GlovesSlot->SetAnimClass(GetMesh()->GetAnimClass());

		PantsSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		PantsSlot->SetAnimClass(GetMesh()->GetAnimClass());

		BootsSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		BootsSlot->SetAnimClass(GetMesh()->GetAnimClass());

		ShoulderSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		ShoulderSlot->SetAnimClass(GetMesh()->GetAnimClass());

		BeltSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
		BeltSlot->SetAnimClass(GetMesh()->GetAnimClass());
	}
}

void AMDEnhancedCharacter::GenerateEquipmentSlots()
{
	if (GetMesh())
	{
		HelmetSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("HelmetSlot");
		HelmetSlot->SetupAttachment(GetMesh());
		HelmetSlot->SetMasterPoseComponent(GetMesh());

		ChestSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("ChestSlot");
		ChestSlot->SetupAttachment(GetMesh());
		ChestSlot->SetMasterPoseComponent(GetMesh());

		GlovesSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("GlovesSlot");
		GlovesSlot->SetupAttachment(GetMesh());
		GlovesSlot->SetMasterPoseComponent(GetMesh());

		PantsSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("PantsSlot");
		PantsSlot->SetupAttachment(GetMesh());
		PantsSlot->SetMasterPoseComponent(GetMesh());

		BootsSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("BootsSlot");
		BootsSlot->SetupAttachment(GetMesh());
		BootsSlot->SetMasterPoseComponent(GetMesh());

		ShoulderSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("ShoulderSlot");
		ShoulderSlot->SetupAttachment(GetMesh());
		ShoulderSlot->SetMasterPoseComponent(GetMesh());

		BeltSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("BeltSlot");
		BeltSlot->SetupAttachment(GetMesh());
		BeltSlot->SetMasterPoseComponent(GetMesh());
	}
}

AMDEnhancedCharacter::AMDEnhancedCharacter()
{
	GenerateEquipmentSlots();
}

void AMDEnhancedCharacter::EquipItem(EMDEquipmentAttachment Attachment, FPrimaryAssetId ItemId)
{
	UMDEquipmentDataAsset* Equipment = GetMDGameInstance()->GetCastPrimaryAssetId<UMDEquipmentDataAsset>(ItemId);

	if (Equipment)
	{
		switch (Attachment)
		{
		case EMDEquipmentAttachment::Chest:
			ChestSlot->SetSkeletalMesh(Equipment->EquipmentMesh.Get());

		default:
			UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."))
		}
	}
}

void AMDEnhancedCharacter::EquipItem(EMDWeaponAttachment Attachment, FPrimaryAssetId ItemId)
{
}

void AMDEnhancedCharacter::EquipItem(EMDAccessoryAttachment Attachment, FPrimaryAssetId ItemId)
{
}

void AMDEnhancedCharacter::UnequipItem(EMDEquipmentAttachment Attachment)
{
	switch (Attachment)
	{
	case EMDEquipmentAttachment::Chest:
		ChestSlot->SetSkeletalMeshWithoutResettingAnimation(nullptr);

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."))
	}
}

bool AMDEnhancedCharacter::IsSlotEquipped(EMDEquipmentAttachment Attachment) const
{
	bool IsEquipped = false;

	switch (Attachment)
	{
	case EMDEquipmentAttachment::Chest:
		if (ChestSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."))
	}

	return IsEquipped;
}

void AMDEnhancedCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupEquipmentSlots();
}

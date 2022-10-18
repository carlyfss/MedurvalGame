// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Actors/Characters/MDEnhancedCharacter.h"

#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Items/MDEquipmentDataAsset.h"

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
		case EMDEquipmentAttachment::Helmet:
			HelmetSlot->SetSkeletalMesh(Equipment->EquipableMesh.Get());
			break;
			
		case EMDEquipmentAttachment::Chest:
			ChestSlot->SetSkeletalMesh(Equipment->EquipableMesh.Get());
			break;

		case EMDEquipmentAttachment::Gloves:
			GlovesSlot->SetSkeletalMesh(Equipment->EquipableMesh.Get());
			break;

		case EMDEquipmentAttachment::Pants:
			PantsSlot->SetSkeletalMesh(Equipment->EquipableMesh.Get());
			break;

		case EMDEquipmentAttachment::Boots:
			BootsSlot->SetSkeletalMesh(Equipment->EquipableMesh.Get());
			break;

		case EMDEquipmentAttachment::None:
			UE_LOG(LogTemp, Warning, TEXT("Equipment attachment was not defined."));
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."));
			break;
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
	case EMDEquipmentAttachment::Helmet:
		HelmetSlot->SetSkeletalMesh(nullptr);
		break;
			
	case EMDEquipmentAttachment::Chest:
		ChestSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDEquipmentAttachment::Gloves:
		GlovesSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDEquipmentAttachment::Pants:
		PantsSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDEquipmentAttachment::Boots:
		BootsSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDEquipmentAttachment::None:
		UE_LOG(LogTemp, Warning, TEXT("Equipment attachment was not defined."));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."));
		break;
	}
}

void AMDEnhancedCharacter::UnequipItem(EMDWeaponAttachment Attachment)
{
}

void AMDEnhancedCharacter::UnequipItem(EMDAccessoryAttachment Attachment)
{
}

bool AMDEnhancedCharacter::IsSlotEquipped(EMDEquipmentAttachment Attachment) const
{
	bool IsEquipped = false;

	switch (Attachment)
	{
	case EMDEquipmentAttachment::Helmet:
		if (HelmetSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;
		
	case EMDEquipmentAttachment::Chest:
		if (ChestSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDEquipmentAttachment::Gloves:
		if (GlovesSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDEquipmentAttachment::Pants:
		if (PantsSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDEquipmentAttachment::Boots:
		if (BootsSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDEquipmentAttachment::None:
		UE_LOG(LogTemp, Warning, TEXT("Equipment attachment was not defined."));
		break;
		
	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Equipment."))
		break;
	}

	return IsEquipped;
}

bool AMDEnhancedCharacter::IsSlotEquipped(EMDWeaponAttachment Attachment) const
{
	return true;
}

bool AMDEnhancedCharacter::IsSlotEquipped(EMDAccessoryAttachment Attachment) const
{
	return true;
}

void AMDEnhancedCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupEquipmentSlots();
}

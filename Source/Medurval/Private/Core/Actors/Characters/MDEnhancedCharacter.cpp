// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Core/Actors/Characters/MDEnhancedCharacter.h"

#include "Core/Actors/Characters/MDDamageableCharacter.h"
#include "Core/Components/MDStaticMeshComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Inventory/Items/MDAccessoryDataAsset.h"
#include "Inventory/Items/MDEquipmentDataAsset.h"
#include "Inventory/Items/MDWeaponDataAsset.h"

void AMDEnhancedCharacter::SetupEquipmentSlots()
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
}

void AMDEnhancedCharacter::GenerateEquipmentSlots()
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
}

void AMDEnhancedCharacter::SetupAccessorySlots()
{
	ShoulderSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	ShoulderSlot->SetAnimClass(GetMesh()->GetAnimClass());

	BeltSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	BeltSlot->SetAnimClass(GetMesh()->GetAnimClass());

	BackSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	BackSlot->SetAnimClass(GetMesh()->GetAnimClass());
}

void AMDEnhancedCharacter::GenerateAccessorySlots()
{
	ShoulderSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("ShoulderSlot");
	ShoulderSlot->SetupAttachment(GetMesh());
	ShoulderSlot->SetMasterPoseComponent(GetMesh());

	BeltSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("BeltSlot");
	BeltSlot->SetupAttachment(GetMesh());
	BeltSlot->SetMasterPoseComponent(GetMesh());

	BackSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("BackSlot");
	BackSlot->SetupAttachment(GetMesh());
	BackSlot->SetMasterPoseComponent(GetMesh());
}

void AMDEnhancedCharacter::SetupWeaponSlots()
{
	PrimaryWeaponSheathSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	PrimaryWeaponSheathSlot->SetAnimClass(GetMesh()->GetAnimClass());

	SecondaryWeaponSheathSlot->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	SecondaryWeaponSheathSlot->SetAnimClass(GetMesh()->GetAnimClass());
}

void AMDEnhancedCharacter::GenerateWeaponSlots()
{
	PrimaryWeaponSlot = CreateDefaultSubobject<UMDStaticMeshComponent>("PrimaryWeaponSlot");
	PrimaryWeaponSlot->SetupAttachment(GetMesh(), PrimaryWeaponSlotSocketName);

	PrimaryWeaponSheathSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("PrimaryWeaponSheathSlot");
	PrimaryWeaponSheathSlot->SetupAttachment(GetMesh());
	PrimaryWeaponSheathSlot->SetMasterPoseComponent(GetMesh());

	SecondaryWeaponSlot = CreateDefaultSubobject<UMDStaticMeshComponent>("SecondaryWeaponSlot");
	SecondaryWeaponSlot->SetupAttachment(GetMesh(), SecondaryWeaponSlotSocketName);

	SecondaryWeaponSheathSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("SecondaryWeaponSheathSlot");
	SecondaryWeaponSheathSlot->SetupAttachment(GetMesh());
	SecondaryWeaponSheathSlot->SetMasterPoseComponent(GetMesh());

	AmmoWeaponSlot = CreateDefaultSubobject<UMDSkeletalMeshComponent>("AmmoWeaponSlot");
	AmmoWeaponSlot->SetupAttachment(GetMesh());
	AmmoWeaponSlot->SetMasterPoseComponent(GetMesh());
}

AMDEnhancedCharacter::AMDEnhancedCharacter()
{
	GenerateEquipmentSlots();
	GenerateAccessorySlots();
	GenerateWeaponSlots();
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
	UMDWeaponDataAsset* Weapon = GetMDGameInstance()->GetCastPrimaryAssetId<UMDWeaponDataAsset>(ItemId);

	if (Weapon)
	{
		switch (Attachment)
		{
		case EMDWeaponAttachment::Primary:
			CombatStyle = Weapon->CombatStyle;
			PrimaryWeaponSlot->SetStaticMesh(Weapon->WeaponEquipableMesh.Get());
			PrimaryWeaponSheathSlot->SetSkeletalMesh(Weapon->EquipableMesh.Get());
			break;

		case EMDWeaponAttachment::Secondary:
			SecondaryWeaponSlot->SetStaticMesh(Weapon->WeaponEquipableMesh.Get());
			SecondaryWeaponSheathSlot->SetSkeletalMesh(Weapon->EquipableMesh.Get());
			break;

		case EMDWeaponAttachment::Ammo:
			AmmoWeaponSlot->SetSkeletalMesh(Weapon->EquipableMesh.Get());
			break;

		case EMDWeaponAttachment::None:
			UE_LOG(LogTemp, Warning, TEXT("Weapon attachment was not defined."));
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Weapon."));
			break;
		}
	}
}

void AMDEnhancedCharacter::EquipItem(EMDAccessoryAttachment Attachment, FPrimaryAssetId ItemId)
{
	UMDAccessoryDataAsset* Accessory = GetMDGameInstance()->GetCastPrimaryAssetId<UMDAccessoryDataAsset>(ItemId);

	if (Accessory)
	{
		switch (Attachment)
		{
		case EMDAccessoryAttachment::Shoulder:
			ShoulderSlot->SetSkeletalMesh(Accessory->EquipableMesh.Get());
			break;

		case EMDAccessoryAttachment::Back:
			BackSlot->SetSkeletalMesh(Accessory->EquipableMesh.Get());
			break;

		case EMDAccessoryAttachment::Belt:
			BeltSlot->SetSkeletalMesh(Accessory->EquipableMesh.Get());
			break;

		case EMDAccessoryAttachment::None:
			UE_LOG(LogTemp, Warning, TEXT("Accessory attachment was not defined."));
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Accessory."));
			break;
		}
	}
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
	switch (Attachment)
	{
	case EMDWeaponAttachment::Primary:
		CombatStyle = EMDCombatStyles::None;
		PrimaryWeaponSlot->SetStaticMesh(nullptr);
		PrimaryWeaponSheathSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDWeaponAttachment::Secondary:
		SecondaryWeaponSlot->SetStaticMesh(nullptr);
		SecondaryWeaponSheathSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDWeaponAttachment::Ammo:
		AmmoWeaponSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDWeaponAttachment::None:
		UE_LOG(LogTemp, Warning, TEXT("Weapon attachment was not defined."));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Weapon."));
		break;
	}
}

void AMDEnhancedCharacter::UnequipItem(EMDAccessoryAttachment Attachment)
{
	switch (Attachment)
	{
	case EMDAccessoryAttachment::Shoulder:
		ShoulderSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDAccessoryAttachment::Back:
		BackSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDAccessoryAttachment::Belt:
		BeltSlot->SetSkeletalMesh(nullptr);
		break;

	case EMDAccessoryAttachment::None:
		UE_LOG(LogTemp, Warning, TEXT("Accessory attachment was not defined."));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Accessory."));
		break;
	}
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
	bool IsEquipped = false;

	switch (Attachment)
	{
	case EMDWeaponAttachment::Primary:
		if (PrimaryWeaponSlot->GetStaticMesh() || PrimaryWeaponSheathSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDWeaponAttachment::Secondary:
		if (SecondaryWeaponSlot->GetStaticMesh() || SecondaryWeaponSheathSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDWeaponAttachment::Ammo:
		if (AmmoWeaponSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDWeaponAttachment::None:
		UE_LOG(LogTemp, Warning, TEXT("Weapon attachment was not defined."));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Weapon."))
		break;
	}

	return IsEquipped;
}

bool AMDEnhancedCharacter::IsSlotEquipped(EMDAccessoryAttachment Attachment) const
{
	bool IsEquipped = false;

	switch (Attachment)
	{
	case EMDAccessoryAttachment::Shoulder:
		if (ShoulderSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDAccessoryAttachment::Back:
		if (BackSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDAccessoryAttachment::Belt:
		if (BeltSlot->SkeletalMesh)
		{
			IsEquipped = true;
		}
		break;

	case EMDAccessoryAttachment::None:
		UE_LOG(LogTemp, Warning, TEXT("Accessory attachment was not defined."));
		break;

	default:
		UE_LOG(LogTemp, Warning, TEXT("Item is not an valid Accessory."))
		break;
	}

	return IsEquipped;
}

void AMDEnhancedCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetupEquipmentSlots();
	SetupAccessorySlots();
	SetupWeaponSlots();
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDCharacter.h"
#include "Core/Enums/MDCombatStyles.h"
#include "GameFramework/Character.h"
#include "Inventory/Enums/MDAccessoryAttachment.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "MDEnhancedCharacter.generated.h"

class UMDStaticMeshComponent;
class UMDSkeletalMeshComponent;
class UMDItemDataAsset;
class UMDGameInstance;

UCLASS()
class MEDURVAL_API AMDEnhancedCharacter : public AMDCharacter
{
	GENERATED_BODY()

#pragma region EquipmentSlots
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> HelmetSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> ChestSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> GlovesSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> PantsSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> BootsSlot;
#pragma endregion EquipmentSlots

#pragma region AccessorySlots
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> ShoulderSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> BeltSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> BackSlot;
#pragma endregion AccessorySlots

#pragma region WeaponSlots
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDStaticMeshComponent> PrimaryWeaponSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	FName PrimaryWeaponSlotSocketName = FName("RightHandSocket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> PrimaryWeaponSheathSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDStaticMeshComponent> SecondaryWeaponSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	FName SecondaryWeaponSlotSocketName = FName("LeftHandSocket");

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> SecondaryWeaponSheathSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> AmmoWeaponSlot;
#pragma endregion WeaponSlots

	UPROPERTY(BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	bool bIsBlocking;

	UPROPERTY(BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	bool bIsRolling;

	UPROPERTY(BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	bool bIsWeaponDrawn;

	UPROPERTY(BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	bool bIsTargetLocked;

	UPROPERTY(BlueprintReadWrite, Category="MDEnhancedCharacter", meta=(AllowPrivateAccess=true))
	EMDCombatStyles CombatStyle = EMDCombatStyles::Fist;
	
protected:
	void SetupEquipmentSlots();

	void GenerateEquipmentSlots();

	void SetupAccessorySlots();

	void GenerateAccessorySlots();

	void SetupWeaponSlots();

	void GenerateWeaponSlots();

public:
	AMDEnhancedCharacter();

	void EquipItem(EMDEquipmentAttachment Attachment, FPrimaryAssetId ItemId);

	void EquipItem(EMDWeaponAttachment Attachment, FPrimaryAssetId ItemId);

	void EquipItem(EMDAccessoryAttachment Attachment, FPrimaryAssetId ItemId);
	
	void UnequipItem(EMDEquipmentAttachment Attachment);

	void UnequipItem(EMDWeaponAttachment Attachment);

	void UnequipItem(EMDAccessoryAttachment Attachment);

	bool IsSlotEquipped(EMDEquipmentAttachment Attachment) const;

	bool IsSlotEquipped(EMDWeaponAttachment Attachment) const;

	bool IsSlotEquipped(EMDAccessoryAttachment Attachment) const;
	
	virtual void BeginPlay() override;
};

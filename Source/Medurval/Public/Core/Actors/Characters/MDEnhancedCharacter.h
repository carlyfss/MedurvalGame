// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "MDCharacter.h"
#include "Core/Components/MDSkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Inventory/Enums/MDAccessoryAttachment.h"
#include "Inventory/Enums/MDEquipmentAttachment.h"
#include "Inventory/Enums/MDWeaponAttachment.h"
#include "MDEnhancedCharacter.generated.h"

class UMDItemDataAsset;
class UMDGameInstance;

UCLASS()
class MEDURVAL_API AMDEnhancedCharacter : public AMDCharacter
{
	GENERATED_BODY()

#pragma region EquipmentSlots
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> HelmetSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> ChestSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> GlovesSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> PantsSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> BootsSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> ShoulderSlot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="MDCharacter|Inputs", meta=(AllowPrivateAccess=true))
	TObjectPtr<UMDSkeletalMeshComponent> BeltSlot;

#pragma endregion EquipmentSlots

	void SetupEquipmentSlots();

	void GenerateEquipmentSlots();

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

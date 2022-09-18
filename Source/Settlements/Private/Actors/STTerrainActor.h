// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Base/STActor.h"
#include "Engine/StreamableManager.h"
#include "Enums/STCivilizationType.h"
#include "Enums/STTerrainSize.h"
#include "Enums/STTerrainStatus.h"
#include "Interfaces/MDInteractableInterface.h"
#include "STTerrainActor.generated.h"

class ASTBuildingActor;
class UMDBoxComponent;

UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="TerrainActor"))
class SETTLEMENTS_API ASTTerrainActor : public ASTActor, public IMDInteractableInterface
{
    GENERATED_BODY()

public:
    ASTTerrainActor();

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDBoxComponent> Collision = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UDecalComponent> Target = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMaterialInterface> DefaultTargetMaterial = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMaterialInstanceDynamic> TargetMaterialInstance = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESTTerrainSize Size = ESTTerrainSize::Small;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESTTerrainStatus Status = ESTTerrainStatus::Unclaimed;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESTCivilizationType Civilization = ESTCivilizationType::Human;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    int ClaimFee = 20;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASTBuildingActor> AssignedBuilding = nullptr;

    UPROPERTY(BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASTBuildingActor> ConstructedBuilding = nullptr;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    float Width = 400.f;

    UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    float Length = 400.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    float MaxLengthWidth = 800.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    float MinLengthWidth = 100.f;

    UPROPERTY(BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    bool bIsSelected = false;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    bool bIsUnderConstruction = false;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    bool bIsClaimable = false;

protected:
    void OnAssignedBuildingLoaded();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void UpdateWidthLengthValues();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SetTargetColor(FLinearColor NewColor);

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    FVector CalculateTerrainSize(float NewWidth, float NewLength);

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SnapSize(float &NewWidth, float &NewLength) const;

public:
    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void LoadAssignedBuilding();
    
    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    bool Claim(ACharacter *OwnerReference, ESTCivilizationType CivilizationType);

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SetIsClaimable(bool bIsTerrainClaimable);

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnClaimed, ASTTerrainActor*, TerrainActor);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnClaimed OnClaimed;

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    bool IsUnclaimed();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void ShowTarget();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void HideTarget();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SelectTarget();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelected, ASTTerrainActor*, TerrainActor);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnSelected OnSelected;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartConstruction, ASTTerrainActor*, TerrainActor);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnStartConstruction OnStartConstruction;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAssignedBuildingLoadCompleted);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnAssignedBuildingLoadCompleted OnAssignedBuildingLoadCompleted;
    
    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void DeselectTarget();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SetAssignedBuilding(TSoftClassPtr<ASTBuildingActor> Building);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="TerrainActor")
    void StartConstruction();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void CompleteConstruction();

    virtual void OnConstruction(const FTransform &Transform) override;

    virtual void BeginPlay() override;

    virtual void OnInteract_Implementation(AActor *InstigatorActor) override;

    UFUNCTION(BlueprintImplementableEvent, Category="TerrainActor")
    void OnTerrainStartFocus();

    UFUNCTION(BlueprintImplementableEvent, Category="TerrainActor")
    void OnTerrainEndFocus();

    virtual void OnStartFocus_Implementation() override;

    virtual void OnEndFocus_Implementation() override;
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SSBuildingActor.h"
#include "Actors/CBActor.h"
#include "Components/CBBoxComponent.h"
#include "Engine/StreamableManager.h"
#include "Enums/SSTerrainSize.h"
#include "Enums/SSTerrainStatus.h"
#include "Interfaces/MDInteractableInterface.h"
#include "SSTerrainActor.generated.h"

UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="TerrainActor"))
class ASSTerrainActor : public ACBActor, public IMDInteractableInterface
{
    GENERATED_BODY()

public:
    ASSTerrainActor();

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBBoxComponent> Collision = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UDecalComponent> Target = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMaterialInterface> DefaultTargetMaterial = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMaterialInstanceDynamic> TargetMaterialInstance = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    FGameplayTag Tag;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESSTerrainSize Size = ESSTerrainSize::Small;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    ESSTerrainStatus Status = ESSTerrainStatus::Unclaimed;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    int ClaimFee = 20;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TSoftClassPtr<ASSBuildingActor> AssignedBuilding = nullptr;

    UPROPERTY(BlueprintReadOnly, Category="TerrainActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<ASSBuildingActor> ConstructedBuilding = nullptr;

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
    bool Claim(ACharacter *OwnerReference);

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    bool IsUnclaimed();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void ShowTarget();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void HideTarget();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SelectTarget();

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelected, ASSTerrainActor*, TerrainActor);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnSelected OnSelected;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStartConstruction, ASSTerrainActor*, TerrainActor);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnStartConstruction OnStartConstruction;

    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAssignedBuildingLoadCompleted);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnAssignedBuildingLoadCompleted OnAssignedBuildingLoadCompleted;
    
    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void DeselectTarget();

    UFUNCTION(BlueprintCallable, Category="TerrainActor")
    void SetAssignedBuilding(TSoftClassPtr<ASSBuildingActor> Building);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="TerrainActor")
    void StartConstruction();

    virtual void OnConstruction(const FTransform &Transform) override;

    virtual void BeginPlay() override;
};

// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Base/STActor.h"
#include "Components/STConstructionComponent.h"
#include "DataAssets/STBuildingDA.h"
#include "Structs/STBuildingTier.h"
#include "STBuildingActor.generated.h"

class UMDStaticMeshComponent;
class USTBuildingTierComponent;
class USTMaintenanceComponent;
class USTSettlementComponent;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="BuildingActor"))
class ASTBuildingActor : public ASTActor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FPrimaryAssetId ConfigurationId;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UMDStaticMeshComponent> Mesh = nullptr;

    UPROPERTY(BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTBuildingDA> ConfigurationReference = nullptr;

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    FSTBuildingTier Tier = FSTBuildingTier();

    UPROPERTY(BlueprintReadWrite, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    ESTCivilizationType Civilization = ESTCivilizationType::Human;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTMaintenanceComponent> MaintenanceComponent = nullptr;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="BuildingActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<USTConstructionComponent> ConstructionComponent = nullptr;
    
protected:
    void LoadConfiguration();

    void OnConfigurationLoaded();

    void FindConstructionMeshes();

    void CheckMeshVisibility() const;
    
public:
    ASTBuildingActor();

    ESTCivilizationType GetCivilization();

    void SetBuildingMesh(UStaticMesh *NewMesh) const;

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void UpdateBuildingConstructionMesh(int Index);
    
    DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfigurationLoadCompleted);
    UPROPERTY(BlueprintCallable, BlueprintAssignable)
    FOnConfigurationLoadCompleted OnConfigurationLoadCompleted;
    
    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category="BuildingActor")
    void OnBeginConstruction();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    void OnConstructionCompleted();

    UFUNCTION(BlueprintCallable, Category="BuildingActor")
    UStaticMesh* GetMeshByCivilization(ESTCivilizationType TargetCivilization) const;

    virtual void BeginPlay() override;
};

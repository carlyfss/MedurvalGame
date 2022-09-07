// MEDURVAL PROJECT copyrighted code by Fireheet Games

#pragma once

#include "CoreMinimal.h"
#include "Base/STActor.h"
#include "STConstructionSiteActor.generated.h"

class UCBStaticMeshComponent;
class UStaticMesh;

UCLASS(Blueprintable, BlueprintType, meta=(DisplayName="ConstructionSiteActor"))
class ASTConstructionSiteActor : public ASTActor
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ConstructionSiteActor", meta=(AllowPrivateAccess=true))
    TObjectPtr<UCBStaticMeshComponent> SiteMesh = nullptr;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="ConstructionSiteActor", meta=(AllowPrivateAccess=true, AssetBundles="World"))
    TSoftObjectPtr<UStaticMesh> ConstructionSiteMesh = nullptr;

protected:
    void SetMesh();

    void LoadConstructionSiteMesh();

    void OnConstructionSiteMeshLoaded();

public:
    ASTConstructionSiteActor();

    virtual void BeginPlay() override;
};

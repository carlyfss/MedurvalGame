// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/STConstructionSiteActor.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Components/MDStaticMeshComponent.h"
#include "Core/Singletons/MDGameInstance.h"
#include "Engine/StreamableManager.h"

ASTConstructionSiteActor::ASTConstructionSiteActor()
{
    SiteMesh = CreateDefaultSubobject<UMDStaticMeshComponent>("Mesh");
    SiteMesh->SetupAttachment(RootComponent);

    SiteMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
    SiteMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void ASTConstructionSiteActor::SetMesh()
{
    if (ConstructionSiteMesh.Get())
    {
        SiteMesh->SetStaticMesh(ConstructionSiteMesh.Get());
    }
    else
    {
        LoadConstructionSiteMesh();
    }
}

void ASTConstructionSiteActor::LoadConstructionSiteMesh()
{
    FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &ASTConstructionSiteActor::OnConstructionSiteMeshLoaded);
    GetMDGameInstance()->LoadObject(ConstructionSiteMesh, Delegate);
}

void ASTConstructionSiteActor::OnConstructionSiteMeshLoaded()
{
    if (ConstructionSiteMesh.Get())
    {
        SiteMesh->SetStaticMesh(ConstructionSiteMesh.Get());
    }
}

void ASTConstructionSiteActor::BeginPlay()
{
    Super::BeginPlay();

    if (SiteMesh)
    {
        SetMesh();
    }
}

// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/STConstructionSiteActor.h"
#include "Components/CBStaticMeshComponent.h"
#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Engine/StreamableManager.h"

ASTConstructionSiteActor::ASTConstructionSiteActor()
{
    SiteMesh = CreateDefaultSubobject<UCBStaticMeshComponent>("Mesh");
    SiteMesh->SetupAttachment(RootComponent);
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
    LoadObject(ConstructionSiteMesh, Delegate);
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

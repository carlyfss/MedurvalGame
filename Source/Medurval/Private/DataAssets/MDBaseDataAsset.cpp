// MEDURVAL PROJECT copyrighted code by Fireheet Games

#include "DataAssets/MDBaseDataAsset.h"

#include "Core/Singleton/MDGameInstance.h"

UObject* UMDBaseDataAsset::GetAssetObject() const
{
	return Object;
}

// Async load functions
void UMDBaseDataAsset::OnAssetLoaded()
{
	Object = Cast<UStaticMesh>(AssetSoftClassRef->GetDefaultObject());
}

void UMDBaseDataAsset::RequestAsyncLoadObject(const UObject* ObjectOwner)
{
	UMDGameInstance* MDGameInstance = Cast<UMDGameInstance>(ObjectOwner->GetWorld()->GetGameInstance());

	if (!MDGameInstance) { return; }

	ObjectSoftPath = AssetSoftClassRef.ToSoftObjectPath();

	MDGameInstance->AssetLoader.RequestAsyncLoad(ObjectSoftPath,
												 FStreamableDelegate::CreateUObject(
													 this, &UMDBaseDataAsset::OnAssetLoaded));
}

void UMDBaseDataAsset::UnloadObject(const UObject* ObjectOwner)
{
	UMDGameInstance* MDGameInstance = Cast<UMDGameInstance>(ObjectOwner->GetWorld()->GetGameInstance());

	if (!MDGameInstance) { return; }

	if (ObjectSoftPath.IsNull()) { return; }

	Object = nullptr;

	MDGameInstance->AssetLoader.Unload(ObjectSoftPath);
}





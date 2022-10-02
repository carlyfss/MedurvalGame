#include "Core/Libraries/MDBlueprintLibrary.h"

#include "MDLoadingScreen.h"

UMDBlueprintLibrary::UMDBlueprintLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UMDBlueprintLibrary::PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime)
{
	IMDLoadingScreenModule& LoadingScreenModule = IMDLoadingScreenModule::Get();
	LoadingScreenModule.StartInGameLoadingScreen(bPlayUntilStopped, PlayTime);
}

void UMDBlueprintLibrary::StopLoadingScreen()
{
	IMDLoadingScreenModule& LoadingScreenModule = IMDLoadingScreenModule::Get();
	LoadingScreenModule.StopInGameLoadingScreen();
}

bool UMDBlueprintLibrary::IsInEditor()
{
	return GIsEditor;
}

FString UMDBlueprintLibrary::GetProjectVersion()
{
	FString ProjectVersion;

	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		ProjectVersion,
		GGameIni
	);

	return ProjectVersion;
}

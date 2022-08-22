#include "Settlements.h"

DEFINE_LOG_CATEGORY(Settlements);

#define LOCTEXT_NAMESPACE "FSettlements"

void FSettlements::StartupModule()
{
	UE_LOG(Settlements, Warning, TEXT("Settlements module has been loaded"));
}

void FSettlements::ShutdownModule()
{
	UE_LOG(Settlements, Warning, TEXT("Settlements module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSettlements, Settlements)
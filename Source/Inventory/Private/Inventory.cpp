#include "Inventory.h"

DEFINE_LOG_CATEGORY(Inventory);

#define LOCTEXT_NAMESPACE "FInventory"

void FInventory::StartupModule()
{
	UE_LOG(Inventory, Warning, TEXT("Inventory module has been loaded"));
}

void FInventory::ShutdownModule()
{
	UE_LOG(Inventory, Warning, TEXT("Inventory module has been unloaded"));
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FInventory, Inventory)
// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Base/STActor.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

USTSettlementSubsystem *ASTActor::GetSettlementSubsystem() const
{
    USTSettlementSubsystem *Subsystem = GetMDGameInstance()->GetSubsystem<USTSettlementSubsystem>();

    if (!Subsystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("Settlement subsystem not available!"));
    }

    return Subsystem;
}

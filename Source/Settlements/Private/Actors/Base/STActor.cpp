// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Base/STActor.h"

#include "Core/AssetManager/MedurvalAssetManager.h"
#include "Core/Singletons/MDGameInstance.h"

USTSettlementSubsystem *ASTActor::GetSettlementSubsystem() const
{
    USTSettlementSubsystem *Subsystem = GetMDGameInstance()->GetSubsystem<USTSettlementSubsystem>();

    if (!Subsystem)
    {
        UE_LOG(LogTemp, Warning, TEXT("Settlement subsystem not available!"));
    }

    return Subsystem;
}

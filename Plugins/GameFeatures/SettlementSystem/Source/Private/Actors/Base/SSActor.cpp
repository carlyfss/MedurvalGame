// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Base/SSActor.h"

#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMDGameInstance * ASSActor::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

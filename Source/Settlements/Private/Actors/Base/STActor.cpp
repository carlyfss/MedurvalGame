// MEDURVAL PROJECT copyrighted code by Fireheet Games


#include "Actors/Base/STActor.h"

#include "Core/Singleton/MDGameInstance.h"
#include "Kismet/GameplayStatics.h"

UMDGameInstance * ASTActor::GetMDGameInstance() const
{
    return Cast<UMDGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

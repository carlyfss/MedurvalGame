// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FRadarCompassModule : public IModuleInterface
{
public:
    //~IModuleInterface
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
    //~End of IModuleInterface
};

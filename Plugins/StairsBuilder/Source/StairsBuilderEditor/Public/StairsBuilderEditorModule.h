#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FStairsBuilderEditorModule : public IModuleInterface
{
public:
	void StartupModule() override;
	void ShutdownModule() override;
};

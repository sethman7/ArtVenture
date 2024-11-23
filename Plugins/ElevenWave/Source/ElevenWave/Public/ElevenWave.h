// Oyintare Ebelo 2023.

#pragma once



#include "Modules/ModuleManager.h"

class FElevenWaveModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	
};

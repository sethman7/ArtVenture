// Oyintare Ebelo 2023.


#include "ElevenWaveDeveloperSettings.h"

const UElevenWaveDeveloperSettings* UElevenWaveDeveloperSettings::Get()
{
	return GetDefault<UElevenWaveDeveloperSettings>();
}

FName UElevenWaveDeveloperSettings::GetCategoryName() const
{
	return "Plugins";
}

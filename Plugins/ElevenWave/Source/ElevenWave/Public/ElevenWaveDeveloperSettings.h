// Oyintare Ebelo 2023.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ElevenWaveDeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(Config=ElevenWaveVoice,meta=(DisplayName="Eleven Wave"))
class ELEVENWAVE_API UElevenWaveDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	
	static const UElevenWaveDeveloperSettings * Get();

	// Base Api Url i.e. https://api.elevenlabs.io/v1 or https://api.elevenlabs.io/v2
	UPROPERTY(Config,EditAnywhere,Category="ElevenWave")
	FString ApiBaseUrl = "https://api.elevenlabs.io/v1";

	// Api Key from Eleven labs
	UPROPERTY(Config, EditAnywhere,Category="ElevenWave")
	FString ApiKey;

	virtual FName GetCategoryName() const override;
};

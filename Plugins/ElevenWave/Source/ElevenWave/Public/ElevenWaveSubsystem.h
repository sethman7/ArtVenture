// Oyintare Ebelo 2023.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ElevenWaveSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class ELEVENWAVE_API UElevenWaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Base Api Url i.e. https://api.elevenlabs.io/v1 or https://api.elevenlabs.io/v2
	UPROPERTY(EditAnywhere,Category="ElevenWave")
	FString ApiBaseUrl;

	// Api Key from Eleven labs
	UPROPERTY(EditAnywhere,Category="ElevenWave")
	FString ApiKey;
	
};

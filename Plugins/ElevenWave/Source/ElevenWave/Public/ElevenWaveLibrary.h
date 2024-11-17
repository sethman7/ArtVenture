// Oyintare Ebelo 2023.

#pragma once

#include "CoreMinimal.h"
#include "ElevenWaveTypes.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Interfaces/IHttpRequest.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ElevenWaveLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ELEVENWAVE_API UElevenWaveLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UPROPERTY()
	FString ApiKey;
public:

	static bool MakeApiRequest(const UObject* WorldContextObject,FString Path,  TFunction<void(FHttpRequestPtr , const FHttpResponsePtr, bool)> Callback,FString Verb = "GET",TFunction<void(const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)> BeforeRequest = nullptr);
	static FElevenWaveDecodedMpeg DecodeMpeg(TArray<uint8> MpegBuffer);

	/**
	 * Updates the Api Key. Must be set before any calls at runtime.
	 * @param Key The New Key
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void UpdateApiKey(const UObject* WorldContextObject,FString Key);

	/**
	 * Updates the Api Base Url. Must be set before any calls at runtime.
	 * @param BaseUrl The New Base Url
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void UpdateApiBaseUrl(const UObject* WorldContextObject,FString BaseUrl = "https://api.elevenlabs.io/v1");

	/**
	 * Gets the current Api Key
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static FString GetApiKey(const UObject* WorldContextObject);

	/**
	 * Gets the current Api Base Url
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static FString GetApiBaseUrl(const UObject* WorldContextObject);
	
	/**
	 * Fetches the available voices from the Eleven Labs API
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void GetAvailableVoices(const UObject* WorldContextObject,const FOnGetAvailableVoicesCompletedDelegate Callback);

	/**
	 * Fetches the models from the Eleven Labs API
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void GetModels(const UObject* WorldContextObject,const FOnGetModelsCompletedDelegate Callback);


	/**
	 * Fetches the specific voice data from the Eleven Labs API
	 * @param VoiceId The id of the voice to fetch
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void GetVoice(const UObject* WorldContextObject,const FString VoiceId,const FOnGetVoiceCompletedDelegate Callback);

	/**
	 * Deletes the specific voice data from the Eleven Labs API
	 * @param VoiceId The id of the voice to delete
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void DeleteVoice(const UObject* WorldContextObject,const FString VoiceId,const FOnDeleteVoiceCompletedDelegate Callback);

	/**
	 * Fetches the default voice settings from the Eleven Labs API
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void GetDefaultVoiceSettings(const UObject* WorldContextObject,const FOnGetDefaultVoiceSettingsCompletedDelegate Callback);

	/**
	 * Fetches the voice settings for the specified VoiceId from the Eleven Labs API
	 * @param VoiceId The id of the voice to fetch settings for
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void GetVoiceSettings(const UObject* WorldContextObject,const FString VoiceId,const FOnGetVoiceSettingsCompletedDelegate Callback);

	/**
	 * Modifies the settings for the specified VoiceId
	 * @param VoiceId The id of the voice to modify
	 * @param Callback The event to call once this task has completed
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void EditVoiceSettings(const UObject* WorldContextObject,const FString VoiceId,FElevenWaveVoiceSettings NewSettings,const FOnEditVoiceSettingsCompletedDelegate Callback);


	
	/**
	 * Generates speech as an mp3/mpeg buffer using the Eleven Labs API
	 * @param Text 
	 * @param VoiceId The VoiceId to Use
	 * @param Callback The event to call once this task has completed
	 * @param VoiceSettings Voice settings to apply to this generation
	 * @param ModelId The ModelId to use
	 * @param OptimizeStreamingLatency 0 - default mode (no latency optimizations) 1 - normal latency optimizations (about 50% of possible latency improvement of option 3) 2 - strong latency optimizations (about 75% of possible latency improvement of option 3) 3 - max latency optimizations 4 - max latency optimizations, but also with text normalizer turned off for even more latency savings (best latency, but can mispronounce eg numbers and dates).
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave",meta = (HidePin = "WorldContextObject", DefaultToSelf = "WorldContextObject"))
	static void TextToSpeech(const UObject* WorldContextObject,FString Text,FString VoiceId,FOnTextToSpeechCompletedDelegate Callback,FElevenWaveVoiceSettings VoiceSettings = FElevenWaveVoiceSettings(),FString ModelId = "eleven_monolingual_v1",int OptimizeStreamingLatency = 0);

	/**
	 * Converts an mp3/mpeg buffer into a playable sound wave
	 * @param ElevenLabsAudio The Data to convert
	 */
	UFUNCTION(BlueprintCallable,Category="ElevenWave")
	static UElevenWaveSoundWave * ToPlayableSound(TArray<uint8> ElevenLabsAudio);
};

// Oyintare Ebelo 2023.


// ReSharper disable CppExpressionWithoutSideEffects
#include "ElevenWaveLibrary.h"

#include "ElevenWaveDeveloperSettings.h"
#include "HttpModule.h"
// ReSharper disable once CppUnusedIncludeDirective
#include "Interfaces/IHttpResponse.h"
#include "dr_mp3.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "ElevenWaveSoundWave.h"
#include "ElevenWaveSubsystem.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"





bool UElevenWaveLibrary::MakeApiRequest(const UObject* WorldContextObject,FString Path,
                                        TFunction<void(FHttpRequestPtr, const FHttpResponsePtr, bool)>
                                        Callback, FString Verb,
                                        TFunction<void(
	                                        const TSharedRef<IHttpRequest, ESPMode::ThreadSafe> Request)>
                                        BeforeRequest)
{
	if(const auto World = WorldContextObject->GetWorld())
	{
		if (Callback)
		{
			if(auto Subsystem = World->GetGameInstance()->GetSubsystem<UElevenWaveSubsystem>())
			{
				const auto HttpModule = &FHttpModule::Get();

				const auto Request = HttpModule->CreateRequest();
				Request->OnProcessRequestComplete().BindLambda(Callback);
				Request->SetURL(UElevenWaveLibrary::GetApiBaseUrl(WorldContextObject) + Path);
				Request->SetVerb(Verb);
				Request->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-ElevenWavePlugin");
				Request->SetHeader("Content-Type", TEXT("application/json"));
				Request->SetHeader("xi-api-key", UElevenWaveLibrary::GetApiKey(WorldContextObject));
				
				if (BeforeRequest) BeforeRequest(Request);

				return Request->ProcessRequest();
			}
			
		}

		
	}
	return false;
}

FElevenWaveDecodedMpeg UElevenWaveLibrary::DecodeMpeg(TArray<uint8> MpegBuffer)
{
	drmp3 MP3_Decoder;

	if (!drmp3_init_memory(&MP3_Decoder, MpegBuffer.GetData(), MpegBuffer.Num(), nullptr))
	{
		return FElevenWaveDecodedMpeg();
	}

	const drmp3_uint64 PCMFrameCount = drmp3_get_pcm_frame_count(&MP3_Decoder);

	// Allocating memory for PCM data
	float* TempPCMData = static_cast<float*>(FMemory::Malloc(PCMFrameCount * MP3_Decoder.channels * sizeof(float)));

	if (!TempPCMData)
	{
		drmp3_uninit(&MP3_Decoder);
		return FElevenWaveDecodedMpeg();
	}

	FElevenWaveDecodedMpeg DecodedData;

	// Filling in PCM data and getting the number of frames
	DecodedData.PcmFrameCount = drmp3_read_pcm_frames_f32(&MP3_Decoder, PCMFrameCount, TempPCMData);

	// Getting PCM data size
	const int64 TempPCMDataSize = static_cast<int64>(DecodedData.PcmFrameCount * MP3_Decoder.channels);

	DecodedData.PcmData = FElevenWaveRuntimeBulkDataBuffer<float>(TempPCMData, TempPCMDataSize);

	// Getting basic audio information
	DecodedData.Duration = static_cast<float>(PCMFrameCount) / MP3_Decoder.sampleRate;
	DecodedData.Channels = MP3_Decoder.channels;
	DecodedData.SampleRate = MP3_Decoder.sampleRate;

	drmp3_uninit(&MP3_Decoder);

	return DecodedData;
}

void UElevenWaveLibrary::UpdateApiKey(const UObject* WorldContextObject,FString Key)
{
	if(const auto World = WorldContextObject->GetWorld())
	{
		
			if(const auto Subsystem = World->GetGameInstance()->GetSubsystem<UElevenWaveSubsystem>())
			{
				if(UKismetSystemLibrary::IsPackagedForDistribution())
				{
					Subsystem->ApiKey = Key;
				}else
				{
					const auto Settings = NewObject<UElevenWaveDeveloperSettings>();
					Settings->ApiKey = Key;
					Settings->SaveConfig();
				}
				
			}
	}
	
}

void UElevenWaveLibrary::UpdateApiBaseUrl(const UObject* WorldContextObject,FString BaseUrl)
{
	if(const auto World = WorldContextObject->GetWorld())
	{
		
		if(const auto Subsystem = World->GetGameInstance()->GetSubsystem<UElevenWaveSubsystem>())
		{
			if(UKismetSystemLibrary::IsPackagedForDistribution())
			{
				Subsystem->ApiBaseUrl = BaseUrl;
			}else
			{
				const auto Settings = NewObject<UElevenWaveDeveloperSettings>();
				Settings->ApiBaseUrl = BaseUrl;
				Settings->SaveConfig();
			}
			
		}
	}
	
}

FString UElevenWaveLibrary::GetApiKey(const UObject* WorldContextObject)
{
	if(const auto World = WorldContextObject->GetWorld())
	{
		
		if(const auto Subsystem = World->GetGameInstance()->GetSubsystem<UElevenWaveSubsystem>())
		{
			if(UKismetSystemLibrary::IsPackagedForDistribution())
			{
				return Subsystem->ApiKey;
			}else
			{
				return UElevenWaveDeveloperSettings::Get()->ApiKey;
			}
		}
	}
	return  "";
}

FString UElevenWaveLibrary::GetApiBaseUrl(const UObject* WorldContextObject)
{
	if(const auto World = WorldContextObject->GetWorld())
	{
		
		if(const auto Subsystem = World->GetGameInstance()->GetSubsystem<UElevenWaveSubsystem>())
		{
			if(UKismetSystemLibrary::IsPackagedForDistribution())
			{
				return Subsystem->ApiBaseUrl;
			}else
			{
				return UElevenWaveDeveloperSettings::Get()->ApiBaseUrl;
			}
		}
	}
	return  "";
}

void UElevenWaveLibrary::GetAvailableVoices(const UObject* WorldContextObject,const FOnGetAvailableVoicesCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/voices", [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	{
		if (bWasSuccessful && Response->GetResponseCode() == 200)
		{
			TSharedPtr<FJsonObject> JsonObject;

			//Deserialize the json data given Reader and the actual object to deserialize
			if (const auto Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
				FJsonSerializer::Deserialize(Reader, JsonObject))
			{
				auto VoicesFound = TArray<FElevenWaveVoice>();
				auto VoiceObjects = JsonObject->GetArrayField("voices");
				for (const auto VoiceObject : VoiceObjects)
				{
					VoicesFound.Add(FElevenWaveVoice(VoiceObject->AsObject()));
				}

				Callback.ExecuteIfBound(true, VoicesFound);
				return;
			}
		}


		Callback.ExecuteIfBound(false, TArray<FElevenWaveVoice>());
	}))
	{
		Callback.ExecuteIfBound(false, TArray<FElevenWaveVoice>());
	}
}

void UElevenWaveLibrary::GetModels(const UObject* WorldContextObject,const FOnGetModelsCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/models", [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	{
		if (bWasSuccessful && Response->GetResponseCode() == 200)
		{
			TArray<TSharedPtr<FJsonValue>> JsonArray;

			//Deserialize the json data given Reader and the actual object to deserialize
			if (const auto Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
				FJsonSerializer::Deserialize(Reader, JsonArray))
			{
				auto ModelsFound = TArray<FElevenWaveModel>();
				for (const auto ModelObject : JsonArray)
				{
					ModelsFound.Add(FElevenWaveModel(ModelObject->AsObject()));
				}

				Callback.ExecuteIfBound(true, ModelsFound);
				return;
			}
		}

		Callback.ExecuteIfBound(false, TArray<FElevenWaveModel>());
	}))
	{
		Callback.ExecuteIfBound(false, TArray<FElevenWaveModel>());
	}
}

void UElevenWaveLibrary::GetVoice(const UObject* WorldContextObject,const FString VoiceId, const FOnGetVoiceCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/voices/" + VoiceId,
	                              [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	                              {
		                              if (bWasSuccessful && Response->GetResponseCode() == 200)
		                              {
			                              TSharedPtr<FJsonObject> JsonObject;

			                              //Deserialize the json data given Reader and the actual object to deserialize
			                              if (const auto Reader = TJsonReaderFactory<TCHAR>::Create(
					                              Response->GetContentAsString());
				                              FJsonSerializer::Deserialize(Reader, JsonObject))
			                              {
				                              Callback.ExecuteIfBound(true, FElevenWaveVoice(JsonObject));
				                              return;
			                              }
		                              }

		                              Callback.ExecuteIfBound(false, FElevenWaveVoice());
	                              }))
	{
		Callback.ExecuteIfBound(false, FElevenWaveVoice());
	}
}

void UElevenWaveLibrary::DeleteVoice(const UObject* WorldContextObject,const FString VoiceId, const FOnDeleteVoiceCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/voices/" + VoiceId,
	                              [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	                              {
		                              if (bWasSuccessful && Response->GetResponseCode() == 200)
		                              {
			                              Callback.ExecuteIfBound(true, Response->GetContentAsString());
			                              return;
		                              }

		                              Callback.ExecuteIfBound(false, "");
	                              }, "DELETE"))
	{
		Callback.ExecuteIfBound(false, "");
	}
}

void UElevenWaveLibrary::GetDefaultVoiceSettings(const UObject* WorldContextObject,const FOnGetDefaultVoiceSettingsCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/voices/settings/default",
	                              [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	                              {
		                              if (bWasSuccessful && Response->GetResponseCode() == 200)
		                              {
			                              TSharedPtr<FJsonObject> JsonObject;

			                              //Deserialize the json data given Reader and the actual object to deserialize
			                              if (const auto Reader = TJsonReaderFactory<TCHAR>::Create(
					                              Response->GetContentAsString());
				                              FJsonSerializer::Deserialize(Reader, JsonObject))
			                              {
				                              Callback.ExecuteIfBound(true, FElevenWaveVoiceSettings(JsonObject));
				                              return;
			                              }
		                              }

		                              Callback.ExecuteIfBound(false, FElevenWaveVoiceSettings());
	                              }))
	{
		Callback.ExecuteIfBound(false, FElevenWaveVoiceSettings());
	}
}

void UElevenWaveLibrary::GetVoiceSettings(const UObject* WorldContextObject,const FString VoiceId,
                                               const FOnGetVoiceSettingsCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/voices/" + VoiceId + "/settings",
	                              [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	                              {
		                              if (bWasSuccessful && Response->GetResponseCode() == 200)
		                              {
			                              TSharedPtr<FJsonObject> JsonObject;

			                              //Deserialize the json data given Reader and the actual object to deserialize
			                              if (const auto Reader = TJsonReaderFactory<TCHAR>::Create(
					                              Response->GetContentAsString());
				                              FJsonSerializer::Deserialize(Reader, JsonObject))
			                              {
				                              Callback.ExecuteIfBound(true, FElevenWaveVoiceSettings(JsonObject));
				                              return;
			                              }
		                              }

		                              Callback.ExecuteIfBound(false, FElevenWaveVoiceSettings());
	                              }))
	{
		Callback.ExecuteIfBound(false, FElevenWaveVoiceSettings());
	}
}

void UElevenWaveLibrary::EditVoiceSettings(const UObject* WorldContextObject,const FString VoiceId, const FElevenWaveVoiceSettings NewSettings,
                                                const FOnEditVoiceSettingsCompletedDelegate Callback)
{
	if (!MakeApiRequest(WorldContextObject,"/voices/" + VoiceId + "/settings/edit",
	                              [Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
	                              {
		                              if (bWasSuccessful && Response->GetResponseCode() == 200)
		                              {
			                              TSharedPtr<FJsonObject> JsonObject;

			                              //Deserialize the json data given Reader and the actual object to deserialize
			                              if (const auto Reader = TJsonReaderFactory<TCHAR>::Create(
					                              Response->GetContentAsString());
				                              FJsonSerializer::Deserialize(Reader, JsonObject))
			                              {
				                              Callback.ExecuteIfBound(true, Response->GetContentAsString());
				                              return;
			                              }
		                              }

		                              Callback.ExecuteIfBound(false, "");
	                              }, "POST", [NewSettings](auto Request)
	                              {
		                              const TSharedRef<FJsonObject> Object = MakeShareable(new FJsonObject());
		                              Object->SetField("stability",
		                                               MakeShareable(new FJsonValueNumber(NewSettings.Stability)));
		                              Object->SetField("similarity_boost",
		                                               MakeShareable(
			                                               new FJsonValueNumber(NewSettings.SimilarityBoost)));
		                              FString OutputString;
		                              const auto Writer = TJsonWriterFactory<TCHAR>::Create(
			                              &OutputString);
		                              FJsonSerializer::Serialize(Object, Writer);
		                              Request->SetContentAsString(OutputString);
	                              }))
	{
		Callback.ExecuteIfBound(false, "");
	}
}

void UElevenWaveLibrary::TextToSpeech(const UObject* WorldContextObject,FString Text, FString VoiceId, FOnTextToSpeechCompletedDelegate Callback,
                                           FElevenWaveVoiceSettings VoiceSettings, FString ModelId,
                                           int OptimizeStreamingLatency)
{
	if (!MakeApiRequest(WorldContextObject,
		"/text-to-speech/" + VoiceId + "?optimize_streaming_latency=" +
		FString::FromInt(FMath::Clamp(OptimizeStreamingLatency, 0, 22)),
		[Callback](auto OriginalRequest, const auto Response, auto bWasSuccessful)
		{
			if (bWasSuccessful && Response->GetResponseCode() == 200)
			{
				Callback.ExecuteIfBound(
					true, Response->GetContent());
				return;
			}

			Callback.ExecuteIfBound(false, TArray<uint8>());
		}, "POST", [Text,VoiceSettings,ModelId](auto Request)
		{
			const TSharedRef<FJsonObject> ContentObject = MakeShareable(new FJsonObject());

			ContentObject->SetField("text", MakeShareable(new FJsonValueString(Text)));
			ContentObject->SetField("model_id", MakeShareable(new FJsonValueString(ModelId)));

			const TSharedRef<FJsonObject> VoiceSettingsObject = MakeShareable(new FJsonObject());
			VoiceSettingsObject->SetField("stability", MakeShareable(new FJsonValueNumber(VoiceSettings.Stability)));
			VoiceSettingsObject->SetField("similarity_boost",
			                              MakeShareable(new FJsonValueNumber(VoiceSettings.SimilarityBoost)));

			ContentObject->SetField("voice_settings", MakeShareable(new FJsonValueObject(VoiceSettingsObject)));

			FString OutputString;
			const auto Writer = TJsonWriterFactory<TCHAR>::Create(&OutputString);
			FJsonSerializer::Serialize(ContentObject, Writer);
			Request->SetContentAsString(OutputString);
		}))
	{
		Callback.ExecuteIfBound(false, TArray<uint8>());
	}
}

UElevenWaveSoundWave *  UElevenWaveLibrary::ToPlayableSound(TArray<uint8> ElevenLabsAudio)
{
	return UElevenWaveSoundWave::FromDecodedMpeg(UElevenWaveLibrary::DecodeMpeg(ElevenLabsAudio));
}

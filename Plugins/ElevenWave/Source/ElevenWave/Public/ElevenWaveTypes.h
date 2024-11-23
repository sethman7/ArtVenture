// Oyintare Ebelo 2023.
#pragma once
#include "Dom/JsonObject.h"
#include "Misc/EngineVersionComparison.h"
#include "Dom/JsonValue.h"
#include "ElevenWaveTypes.generated.h"


class UElevenWaveSoundWave;

/**
 * An alternative to FBulkDataBuffer with consistent data types
 */
template <typename DataType>
class FElevenWaveRuntimeBulkDataBuffer
{
public:
#if  UE_VERSION_OLDER_THAN(4, 26, 0)
	using ViewType = TArrayView<DataType>;
#else
	using ViewType = TArrayView64<DataType>;
#endif

	FElevenWaveRuntimeBulkDataBuffer() = default;

	FElevenWaveRuntimeBulkDataBuffer(const FElevenWaveRuntimeBulkDataBuffer& Other)
	{
		*this = Other;
	}

	FElevenWaveRuntimeBulkDataBuffer(FElevenWaveRuntimeBulkDataBuffer&& Other) noexcept
	{
		View = MoveTemp(Other.View);
		Other.View = ViewType();
	}

	FElevenWaveRuntimeBulkDataBuffer(DataType* InBuffer, int64 InNumberOfElements)
		: View(InBuffer, InNumberOfElements)
	{
#if UE_VERSION_OLDER_THAN(4, 26, 0)
		check(InNumberOfElements <= TNumericLimits<int32>::Max())
#endif
	}

	template <typename Allocator>
	explicit FElevenWaveRuntimeBulkDataBuffer(const TArray<DataType, Allocator>& Other)
	{
		const int64 BulkDataSize = Other.Num();

		DataType* BulkData = static_cast<DataType*>(FMemory::Malloc(BulkDataSize * sizeof(DataType)));
		if (!BulkData)
		{
			return;
		}

		FMemory::Memcpy(BulkData, Other.GetData(), BulkDataSize * sizeof(DataType));
		View = ViewType(BulkData, BulkDataSize);
	}

	~FElevenWaveRuntimeBulkDataBuffer()
	{
		FreeBuffer();
	}

	FElevenWaveRuntimeBulkDataBuffer& operator=(const FElevenWaveRuntimeBulkDataBuffer& Other)
	{
		FreeBuffer();

		if (this != &Other)
		{
			const int64 BufferSize = Other.View.Num();

			DataType* BufferCopy = static_cast<DataType*>(FMemory::Malloc(BufferSize * sizeof(DataType)));
			FMemory::Memcpy(BufferCopy, Other.View.GetData(), BufferSize * sizeof(DataType));

			View = ViewType(BufferCopy, BufferSize);
		}

		return *this;
	}

	FElevenWaveRuntimeBulkDataBuffer& operator=(FElevenWaveRuntimeBulkDataBuffer&& Other) noexcept
	{
		if (this != &Other)
		{
			FreeBuffer();

			View = Other.View;
			Other.View = ViewType();
		}

		return *this;
	}

	void Empty()
	{
		FreeBuffer();
		View = ViewType();
	}

	void Reset(DataType* InBuffer, int64 InNumberOfElements)
	{
		FreeBuffer();

#if UE_VERSION_OLDER_THAN(4, 26, 0)
		check(InNumberOfElements <= TNumericLimits<int32>::Max())
#endif

		View = ViewType(InBuffer, InNumberOfElements);
	}

	const ViewType& GetView() const
	{
		return View;
	}

private:
	void FreeBuffer()
	{
		if (View.GetData() != nullptr)
		{
			FMemory::Free(View.GetData());
			View = ViewType();
		}
	}

	ViewType View;
};

USTRUCT()
struct FElevenWaveDecodedMpeg
{
	GENERATED_BODY()

	FElevenWaveRuntimeBulkDataBuffer<float> PcmData;
	int64 PcmFrameCount;
	float Duration;
	int32 Channels;
	int32 SampleRate;
};

USTRUCT()
struct FElevenWavePCMData
{
	GENERATED_BODY()

	FElevenWaveRuntimeBulkDataBuffer<float> PCMData;
	int64 PCMNumOfFrames;
};

USTRUCT(BlueprintType)
struct FElevenWaveLanguage
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString LanguageId = "";
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Name = "";
	
	FElevenWaveLanguage()
	{
		
	}

	FElevenWaveLanguage(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetStringField("language_id",LanguageId);
		JsonObject->TryGetStringField("name",Name);
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceFineTuningVerificationAttemptRecording
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString RecordingId = "";
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString MimeType = "";
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float SizeBytes = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float UploadDateUnix = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Transcription = "";

	FElevenWaveVoiceFineTuningVerificationAttemptRecording()
	{
		
	}

	FElevenWaveVoiceFineTuningVerificationAttemptRecording(const TSharedPtr<FJsonObject> JsonObject)
	{
		 JsonObject->TryGetStringField("recording_id",RecordingId);
		 JsonObject->TryGetStringField("mime_type",MimeType);
		 JsonObject->TryGetNumberField("size_bytes",SizeBytes);
		 JsonObject->TryGetNumberField("upload_date_unix",UploadDateUnix);
		 JsonObject->TryGetStringField("transcription",Transcription);
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceFineTuningVerificationAttempt
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Text = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float DateUnix = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bAccepted = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float Similarity = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float LevenshteinDistance = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FElevenWaveVoiceFineTuningVerificationAttemptRecording Recording;

	FElevenWaveVoiceFineTuningVerificationAttempt()
	{
		
	}

	FElevenWaveVoiceFineTuningVerificationAttempt(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetStringField("text",Text);
		JsonObject->TryGetNumberField("date_unix",DateUnix);
		JsonObject->TryGetBoolField("accepted",bAccepted);
		JsonObject->TryGetNumberField("similarity",Similarity);
		JsonObject->TryGetNumberField("levenshtein_distance",LevenshteinDistance);

		if(const TSharedPtr<FJsonObject> * RecordingTemp; JsonObject->TryGetObjectField("recording",RecordingTemp))
		{
			Recording = FElevenWaveVoiceFineTuningVerificationAttemptRecording(*RecordingTemp);
		}
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceFineTuningManualVerificationFile
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString FileId = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString FileName = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString MimeType = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float SizeBytes = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float UploadDateUnix = 0;
	

	
	FElevenWaveVoiceFineTuningManualVerificationFile()
	{
		
	}

	FElevenWaveVoiceFineTuningManualVerificationFile(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetStringField("file_id",FileId);
		JsonObject->TryGetStringField("file_name",FileName);
		JsonObject->TryGetStringField("mime_type",MimeType);
		JsonObject->TryGetNumberField("size_bytes",SizeBytes);
		JsonObject->TryGetNumberField("upload_date_unix",UploadDateUnix);
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceFineTuningManualVerification
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString ExtraText = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float RequestTimeUnix = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FElevenWaveVoiceFineTuningManualVerificationFile> Files;
	
	FElevenWaveVoiceFineTuningManualVerification()
	{
		
	}

	FElevenWaveVoiceFineTuningManualVerification(const TSharedPtr<FJsonObject> JsonObject)
	{
		
		JsonObject->TryGetStringField("extra_text",ExtraText);
		JsonObject->TryGetNumberField("request_time_unix",RequestTimeUnix);

		if(const TArray<TSharedPtr<FJsonValue>>* Temp; JsonObject->TryGetArrayField("files",Temp))
		{

			for(const TSharedPtr<FJsonValue> File : *Temp)
			{
				Files.Add(FElevenWaveVoiceFineTuningManualVerificationFile(File->AsObject()));
			}
		}
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceFineTuning
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString ModelId = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Language = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bIsAllowedToFineTune = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bFineTuningRequested = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString FineTuningState = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FElevenWaveVoiceFineTuningVerificationAttempt> VerificationAttempts;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FString> VerificationFailures;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	int VerificationAttemptsCount = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FString> SliceIds;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FElevenWaveVoiceFineTuningManualVerification ManualVerification;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bManualVerificationRequested = false;
	
	FElevenWaveVoiceFineTuning()
	{
		
	}

	FElevenWaveVoiceFineTuning(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetStringField("model_id",ModelId);
		JsonObject->TryGetStringField("language",Language);
		JsonObject->TryGetBoolField("is_allowed_to_fine_tune",bIsAllowedToFineTune);
		JsonObject->TryGetBoolField("fine_tuning_requested",bFineTuningRequested);
		JsonObject->TryGetStringField("finetuning_state",FineTuningState);

		if(const TArray<TSharedPtr<FJsonValue>>* Temp; JsonObject->TryGetArrayField("verification_attempts",Temp))
		{
			for(const TSharedPtr<FJsonValue> Attempt : *Temp)
			{
				VerificationAttempts.Add(FElevenWaveVoiceFineTuningVerificationAttempt(Attempt->AsObject()));
			}
		}

		JsonObject->TryGetStringArrayField("verification_failures",VerificationFailures);

		JsonObject->TryGetNumberField("verification_attempts_count",VerificationAttemptsCount);

		JsonObject->TryGetStringArrayField("slice_ids",SliceIds);

		if(const TSharedPtr<FJsonObject> * ManualVerificationTemp; JsonObject->TryGetObjectField("manual_verification",ManualVerificationTemp))
		{
			ManualVerification = FElevenWaveVoiceFineTuningManualVerification(*ManualVerificationTemp);
		}

		JsonObject->TryGetBoolField("manual_verification_requested",bManualVerificationRequested);
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceSharing
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Status = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString HistoryItemSampleId = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bEnabledInLibrary = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString OriginalVoiceId = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString PublicOwnerId = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	int LikedByCount = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	int ClonedByCount = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FString> WhitelistedEmails;

	FElevenWaveVoiceSharing()
	{
		
	}

	FElevenWaveVoiceSharing(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetStringField("status",Status);
		JsonObject->TryGetStringField("history_item_sample_id",HistoryItemSampleId);
		JsonObject->TryGetBoolField("enabled_in_library",bEnabledInLibrary);
		JsonObject->TryGetStringField("original_voice_id",OriginalVoiceId);
		JsonObject->TryGetStringField("public_owner_id",PublicOwnerId);
		JsonObject->TryGetNumberField("liked_by_count",LikedByCount);
		JsonObject->TryGetNumberField("cloned_by_count",ClonedByCount);
		JsonObject->TryGetStringArrayField("whitelisted_emails",WhitelistedEmails);
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceSettings
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float Stability = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float SimilarityBoost = 0;

	FElevenWaveVoiceSettings()
	{
		
	}

	FElevenWaveVoiceSettings(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetNumberField("stability",Stability);
		JsonObject->TryGetNumberField("similarity_boost",SimilarityBoost);
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveVoiceSample
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString VoiceId = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString FileName = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString MimeType = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	int SizeBytes = 0;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Hash = "";

	FElevenWaveVoiceSample()
	{
		
	}

	FElevenWaveVoiceSample(const TSharedPtr<FJsonObject> JsonObject)
	{
		 JsonObject->TryGetStringField("sample_id",VoiceId);
		 JsonObject->TryGetStringField("file_name",FileName);
		 JsonObject->TryGetStringField("mime_type",MimeType);
		 JsonObject->TryGetNumberField("size_bytes",SizeBytes);
		 JsonObject->TryGetStringField("hash",Hash);
	}
};


USTRUCT(BlueprintType)
struct FElevenWaveVoice
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString VoiceId = "";
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Name = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FElevenWaveVoiceSample> Samples;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Category = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FElevenWaveVoiceFineTuning FineTuning;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TMap<FString,FString> Labels;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Description;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString PreviewUrl;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FString> AvailableForTiers;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FElevenWaveVoiceSettings Settings;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FElevenWaveVoiceSharing Sharing;
	
	FElevenWaveVoice(){}

	FElevenWaveVoice(const TSharedPtr<FJsonObject>& JsonObject)
	{
		JsonObject->TryGetStringField("voice_id",VoiceId);
		
		JsonObject->TryGetStringField("name",Name);
		
		if(const TArray<TSharedPtr<FJsonValue>>* Temp; JsonObject->TryGetArrayField("samples",Temp))
		{
			for(const TSharedPtr<FJsonValue> Attempt : *Temp)
			{
				Samples.Add(FElevenWaveVoiceSample(Attempt->AsObject()));
			}
		}

		Category = JsonObject->GetStringField("category");

		if(const TSharedPtr<FJsonObject> * Temp; JsonObject->TryGetObjectField("fine_tuning",Temp))
		{
			FineTuning = FElevenWaveVoiceFineTuning(*Temp);
		}

		if(const TSharedPtr<FJsonObject> * Temp; JsonObject->TryGetObjectField("labels",Temp))
		{
			for(const auto Value : Temp->Get()->Values)
			{
				Labels.Add(Value.Key,Value.Value->AsString());
			}
		}

		JsonObject->TryGetStringField("description",Description);

		JsonObject->TryGetStringField("preview_url",PreviewUrl);

		JsonObject->TryGetStringArrayField("available_for_tiers",AvailableForTiers);
		
		if(const TSharedPtr<FJsonObject> * Temp; JsonObject->TryGetObjectField("settings",Temp))
		{
			Settings = FElevenWaveVoiceSettings(*Temp);
		}

		if(const TSharedPtr<FJsonObject> * Temp; JsonObject->TryGetObjectField("sharing",Temp))
		{
			Sharing = FElevenWaveVoiceSharing(*Temp);
		}
	}
};

USTRUCT(BlueprintType)
struct FElevenWaveModel
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString ModelId = "";
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Name = "";

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bCanBeFineTuned = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bCanDoTextToSpeech = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bCanDoVoiceConversion = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	bool bServesProVoices = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	float TokenCostFactor = 0;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	FString Description;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="ElevenWave")
	TArray<FElevenWaveLanguage> Languages;
	
	FElevenWaveModel(){}

	FElevenWaveModel(const TSharedPtr<FJsonObject> JsonObject)
	{
		JsonObject->TryGetStringField("model_id",ModelId);
		
		JsonObject->TryGetStringField("name",Name);

		JsonObject->TryGetBoolField("can_be_finetuned",bCanBeFineTuned);

		JsonObject->TryGetBoolField("can_do_text_to_speech",bCanDoTextToSpeech);

		JsonObject->TryGetBoolField("can_do_voice_conversion",bCanDoVoiceConversion);

		JsonObject->TryGetBoolField("serves_pro_voices",bServesProVoices);

		JsonObject->TryGetNumberField("token_cost_factor",TokenCostFactor);

		JsonObject->TryGetStringField("description",Description);
		
		if(const TArray<TSharedPtr<FJsonValue>>* Temp; JsonObject->TryGetArrayField("languages",Temp))
		{
			for(const TSharedPtr<FJsonValue> Attempt : *Temp)
			{
				Languages.Add(FElevenWaveLanguage(Attempt->AsObject()));
			}
		}
	}
};


DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetAvailableVoicesCompletedDelegate, bool, bWasSuccessful,const TArray<FElevenWaveVoice>&, Voices);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetVoiceCompletedDelegate, bool, bWasSuccessful,const FElevenWaveVoice, Voice);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnDeleteVoiceCompletedDelegate, bool, bWasSuccessful,FString, Result);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnEditVoiceSettingsCompletedDelegate, bool, bWasSuccessful,FString, Result);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetModelsCompletedDelegate, bool, bWasSuccessful,const TArray<FElevenWaveModel>&, Models);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetDefaultVoiceSettingsCompletedDelegate, bool, bWasSuccessful,const FElevenWaveVoiceSettings, Settings);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnGetVoiceSettingsCompletedDelegate, bool, bWasSuccessful,const FElevenWaveVoiceSettings, Settings);

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnTextToSpeechCompletedDelegate, bool, bWasSuccessful, const TArray<uint8>& , RawSoundData);

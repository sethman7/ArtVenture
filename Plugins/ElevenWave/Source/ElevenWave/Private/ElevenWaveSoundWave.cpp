// Oyintare Ebelo 2023.


#include "ElevenWaveSoundWave.h"
#include "AudioDevice.h"


UElevenWaveSoundWave::UElevenWaveSoundWave(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	PCMBufferInfo = MakeUnique<FElevenWavePCMData>();
	SetSampleRate(0);
	NumChannels = 0;
	Duration = 0;
	bProcedural = true;
	DecompressionType = EDecompressionType::DTYPE_Procedural;
	SoundGroup = ESoundGroup::SOUNDGROUP_Default;
	SetPrecacheState(ESoundWavePrecacheState::Done);
}

UElevenWaveSoundWave * UElevenWaveSoundWave::FromDecodedMpeg(FElevenWaveDecodedMpeg Data)
{
	const auto Obj = NewObject<UElevenWaveSoundWave>();
	Obj->Duration = Data.Duration;
	Obj->NumChannels = Data.Channels;
	Obj->PCMBufferInfo->PCMData = Data.PcmData;
	Obj->PCMBufferInfo->PCMNumOfFrames = Data.PcmFrameCount;
	Obj->SetSampleRate(Data.SampleRate);
#if ENGINE_MAJOR_VERSION >= 5
	Obj->SetImportedSampleRate(0);
#endif
	return Obj;
}

void UElevenWaveSoundWave::BeginDestroy()
{
	Super::BeginDestroy();
}


Audio::EAudioMixerStreamDataFormat::Type UElevenWaveSoundWave::GetGeneratedPCMDataFormat() const
{
	return Audio::EAudioMixerStreamDataFormat::Type::Float;
}

int32 UElevenWaveSoundWave::OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples)
{
	FScopeLock Lock(&DataGuard);

	if (!PCMBufferInfo.IsValid())
	{
		return 0;
	}

	// Ensure there is enough number of frames. Lack of frames means audio playback has finished
	if (GetNumOfPlayedFrames_Internal() >= PCMBufferInfo->PCMNumOfFrames)
	{
		return 0;
	}

	// Getting the remaining number of samples if the required number of samples is greater than the total available number
	if (GetNumOfPlayedFrames_Internal() + (static_cast<uint32>(NumSamples) / static_cast<uint32>(NumChannels)) >= PCMBufferInfo->PCMNumOfFrames)
	{
		NumSamples = (PCMBufferInfo->PCMNumOfFrames - GetNumOfPlayedFrames_Internal()) * NumChannels;
	}

	// Retrieving a part of PCM data
	float* RetrievedPCMDataPtr = PCMBufferInfo->PCMData.GetView().GetData() + (GetNumOfPlayedFrames_Internal() * NumChannels);
	const int32 RetrievedPCMDataSize = NumSamples * sizeof(float);

	// Ensure we got a valid PCM data
	if (RetrievedPCMDataSize <= 0 || !RetrievedPCMDataPtr)
	{
		return 0;
	}

	// Filling in OutAudio array with the retrieved PCM data
	OutAudio = TArray<uint8>(reinterpret_cast<uint8*>(RetrievedPCMDataPtr), RetrievedPCMDataSize);

	// Increasing the number of frames played
	SetNumOfPlayedFrames_Internal(GetNumOfPlayedFrames_Internal() + (NumSamples / NumChannels));

	return NumSamples;
}


void UElevenWaveSoundWave::Parse(FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances)
{
	FScopeLock Lock(&DataGuard);

#if ENGINE_MAJOR_VERSION >= 5
	if (ActiveSound.PlaybackTime == 0.f)
	{
		RewindPlaybackTime_Internal(ParseParams.StartTime);
	}
#endif

	// Stopping all other active sounds that are using the same sound wave, so that only one sound wave can be played at a time
	const TArray<FActiveSound*>& ActiveSounds = AudioDevice->GetActiveSounds();
	for (FActiveSound* ActiveSoundPtr : ActiveSounds)
	{
		if (ActiveSoundPtr->GetSound() == this && &ActiveSound != ActiveSoundPtr)
		{
			AudioDevice->StopActiveSound(ActiveSoundPtr);
		}
	}

	ActiveSound.PlaybackTime = GetPlaybackTime_Internal();

	if (IsPlaybackFinished_Internal())
	{
		

		if (!bLooping)
		{
			AudioDevice->StopActiveSound(&ActiveSound);
		}
		else
		{
			ActiveSound.PlaybackTime = 0.f;
			RewindPlaybackTime_Internal(0.f);
		}
	}

	Super::Parse(AudioDevice, NodeWaveInstanceHash, ActiveSound, ParseParams, WaveInstances);
}



void UElevenWaveSoundWave::ReleaseMemory()
{
	FScopeLock Lock(&DataGuard);
	PCMBufferInfo->PCMData.Empty();
	PCMBufferInfo->PCMNumOfFrames = 0;
}

void UElevenWaveSoundWave::SetLooping(bool bLoop)
{
	bLooping = bLoop;
}


void UElevenWaveSoundWave::SetVolume(float InVolume)
{
	Volume = InVolume;
}

void UElevenWaveSoundWave::SetPitch(float InPitch)
{
	Pitch = InPitch;
}

bool UElevenWaveSoundWave::RewindPlaybackTime_Internal(float PlaybackTime)
{
	if (PlaybackTime > Duration)
	{
		return false;
	}

	return SetNumOfPlayedFrames_Internal(PlaybackTime * SampleRate);
}


bool UElevenWaveSoundWave::SetNumOfPlayedFrames(uint32 NumOfFrames)
{
	FScopeLock Lock(&DataGuard);
	return SetNumOfPlayedFrames_Internal(NumOfFrames);
}

bool UElevenWaveSoundWave::SetNumOfPlayedFrames_Internal(uint32 NumOfFrames)
{
	if (NumOfFrames < 0 || NumOfFrames > PCMBufferInfo->PCMNumOfFrames)
	{

		return false;
	}

	PlayedNumOfFrames = NumOfFrames;

	return true;
}

uint32 UElevenWaveSoundWave::GetNumOfPlayedFrames() const
{
	FScopeLock Lock(&DataGuard);
	return GetNumOfPlayedFrames_Internal();
}

uint32 UElevenWaveSoundWave::GetNumOfPlayedFrames_Internal() const
{
	return PlayedNumOfFrames;
}

float UElevenWaveSoundWave::GetPlaybackTime() const
{
	FScopeLock Lock(&DataGuard);
	return GetPlaybackTime_Internal() + GetDurationOffset_Internal();
}

float UElevenWaveSoundWave::GetPlaybackTime_Internal() const
{
	if (GetNumOfPlayedFrames() == 0 || SampleRate <= 0)
	{
		return 0;
	}

	return static_cast<float>(GetNumOfPlayedFrames()) / SampleRate;
}

float UElevenWaveSoundWave::GetDurationConst() const
{
	FScopeLock Lock(&DataGuard);
	return GetDurationConst_Internal() + GetDurationOffset_Internal();
}

float UElevenWaveSoundWave::GetDurationConst_Internal() const
{
	return Duration;
}

float UElevenWaveSoundWave::GetDuration()
#if ENGINE_MAJOR_VERSION >= 5
const
#endif
{
	return GetDurationConst();
}

int32 UElevenWaveSoundWave::GetSampleRate() const
{
	return SampleRate;
}

int32 UElevenWaveSoundWave::GetNumOfChannels() const
{
	return NumChannels;
}

float UElevenWaveSoundWave::GetPlaybackPercentage() const
{
	FScopeLock Lock(&DataGuard);

	if (GetNumOfPlayedFrames_Internal() == 0 || PCMBufferInfo->PCMNumOfFrames == 0)
	{
		return 0;
	}

	return static_cast<float>(GetNumOfPlayedFrames_Internal()) / PCMBufferInfo->PCMNumOfFrames * 100;
}

bool UElevenWaveSoundWave::IsPlaybackFinished() const
{
	FScopeLock Lock(&DataGuard);
	return IsPlaybackFinished_Internal();
}

float UElevenWaveSoundWave::GetDurationOffset() const
{
	FScopeLock Lock(&DataGuard);
	return DurationOffset;
}

float UElevenWaveSoundWave::GetDurationOffset_Internal() const
{
	return DurationOffset;
}

bool UElevenWaveSoundWave::IsPlaybackFinished_Internal() const
{
	// Are there enough frames for future playback from the current ones or not
	const bool bOutOfFrames = GetNumOfPlayedFrames_Internal() >= PCMBufferInfo->PCMNumOfFrames;

	// Is PCM data valid
	const bool bValidPCMData = PCMBufferInfo.IsValid();

	return bOutOfFrames && bValidPCMData;
}

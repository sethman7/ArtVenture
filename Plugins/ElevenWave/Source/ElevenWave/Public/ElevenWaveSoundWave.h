// Oyintare Ebelo 2023.

#pragma once

#include "CoreMinimal.h"
#include "ElevenWaveTypes.h"
#include "Sound/SoundWaveProcedural.h"
#include "ElevenWaveSoundWave.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class ELEVENWAVE_API UElevenWaveSoundWave : public USoundWaveProcedural
{
	GENERATED_BODY()

public:


	UElevenWaveSoundWave(const FObjectInitializer& ObjectInitializer);

	static UElevenWaveSoundWave * FromDecodedMpeg(FElevenWaveDecodedMpeg Data);
	
	TUniquePtr<FElevenWavePCMData> PCMBufferInfo;
	
	virtual void BeginDestroy() override;
	virtual void Parse(class FAudioDevice* AudioDevice, const UPTRINT NodeWaveInstanceHash, FActiveSound& ActiveSound, const FSoundParseParameters& ParseParams, TArray<FWaveInstance*>& WaveInstances) override;

	virtual Audio::EAudioMixerStreamDataFormat::Type GetGeneratedPCMDataFormat() const override;
	//~ Begin USoundWaveProcedural Interface
	virtual int32 OnGeneratePCMAudio(TArray<uint8>& OutAudio, int32 NumSamples) override;
	//~ End USoundWaveProcedural Interface

	/**
	 * Release sound wave data. Call it manually only if you are sure of it
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	virtual void ReleaseMemory();
	

	/**
	 * Set whether the sound should loop or not
	 *
	 * @param bLoop Whether the sound should loop or not
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	void SetLooping(bool bLoop);
	

	/**
	 * Set sound playback volume
	 *
	 * @param InVolume Volume
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	void SetVolume(UPARAM(DisplayName = "Volume") float InVolume = 1);

	/**
	 * Set sound playback pitch
	 *
	 * @param InPitch Pitch
	 */
	UFUNCTION(BlueprintCallable, Category = "Imported Sound Wave|Properties")
	void SetPitch(UPARAM(DisplayName = "Pitch") float InPitch = 1);
	
	/**
	 * Thread-unsafe equivalent of RewindPlaybackTime
	 * Should only be used if DataGuard is locked
	 * @note This does not add a duration offset
	 */
	bool RewindPlaybackTime_Internal(float PlaybackTime);
	
	/**
	 * Change the number of frames played back. Used to rewind the sound
	 *
	 * @param NumOfFrames The new number of frames from which to continue playing sound
	 * @return Whether the frames were changed or not
	 */
	bool SetNumOfPlayedFrames(uint32 NumOfFrames);

	/**
	 * Thread-unsafe equivalent of SetNumOfPlayedFrames
	 * Should only be used if DataGuard is locked
	 */
	bool SetNumOfPlayedFrames_Internal(uint32 NumOfFrames);

	/**
	 * Get the number of frames played back
	 *
	 * @return The number of frames played back
	 */
	uint32 GetNumOfPlayedFrames() const;

	/**
	 * Thread-unsafe equivalent of GetNumOfPlayedFrames
	 * Should only be used if DataGuard is locked
	 */
	uint32 GetNumOfPlayedFrames_Internal() const;

	/**
	 * Get the current sound wave playback time, in seconds
	 * @note This adds a duration offset (relevant if ReleasePlayedAudioData was used)
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	float GetPlaybackTime() const;

	/**
	 * Thread-unsafe equivalent of GetPlaybackTime
	 * Should only be used if DataGuard is locked
	 * @note This does not add a duration offset
	 */
	float GetPlaybackTime_Internal() const;

	/**
	 * Constant alternative for getting the length of the sound wave, in seconds
	 * @note This adds a duration offset (relevant if ReleasePlayedAudioData was used)
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound", meta = (DisplayName = "Get Duration"))
	float GetDurationConst() const;

	/**
	 * Thread-unsafe equivalent of GetDurationConst
	 * Should only be used if DataGuard is locked
	 * @note This does not add a duration offset
	 */
	float GetDurationConst_Internal() const;

	/**
	 * Get the length of the sound wave, in seconds
	 * @note This adds a duration offset (relevant if ReleasePlayedAudioData was used)
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	virtual float GetDuration()
#if ENGINE_MAJOR_VERSION < 5
	override;
#else
	const override;
#endif

	/**
	 * Get sample rate
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	int32 GetSampleRate() const;

	/**
	 * Get number of channels
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	int32 GetNumOfChannels() const;

	/**
	 * Get the current sound playback percentage, 0-100%
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	float GetPlaybackPercentage() const;

	/**
	 * Check if audio playback has finished or not
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	bool IsPlaybackFinished() const;

	/**
	 * Get the duration offset if some played back audio data was removed during playback (eg in ReleasePlayedAudioData)
	 * The sound wave starts playing from this time as from the very beginning
	 */
	UFUNCTION(BlueprintCallable, Category = "ElevenWave|Sound")
	float GetDurationOffset() const;

	/**
	 * Thread-unsafe equivalent of GetDurationOffset
	 * Should only be used if DataGuard is locked
	 */
	float GetDurationOffset_Internal() const;

	/**
	 * Thread-unsafe equivalent of IsPlaybackFinished
	 * Should only be used if DataGuard is locked
	 */
	bool IsPlaybackFinished_Internal() const;


	/** Data guard (mutex) for thread safety */
	mutable FCriticalSection DataGuard;

	/** The number of frames played. Increments during playback, should not be > PCMBufferInfo.PCMNumOfFrames */
	uint32 PlayedNumOfFrames;

	/** Duration offset, needed to track the clearing of part of the audio data of the sound wave during playback (see ReleasePlayedAudioData) */
	float DurationOffset;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/AVPlayerController.h"

void AAVPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
}

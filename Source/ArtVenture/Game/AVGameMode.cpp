// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AVGameMode.h"

AAVGameMode::AAVGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ArtVenture/TempPlayer/Blueprints/BP_FirstPersonCharacter.BP_FirstPersonCharacter_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Game/ArtVenture/TempPlayer/Blueprints/BP_FirstPersonPlayerController.BP_FirstPersonPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AVGameMode.h"
//#include "UObject/ConstructorHelpers.h"
//#include "Engine/World.h"

AAVGameMode::AAVGameMode()
{
	

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ArtVenture/TempPlayer/Blueprints/BP_FirstPersonCharacter.BP_FirstPersonCharacter_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerControllerBPRef(TEXT("/Game/ArtVenture/TempPlayer/Blueprints/BP_FirstPersonPlayerController.BP_FirstPersonPlayerController"));
	if (PlayerControllerBPRef.Object)
	{
		PlayerControllerClass = (UClass*)PlayerControllerBPRef.Object->GeneratedClass;
	}
}


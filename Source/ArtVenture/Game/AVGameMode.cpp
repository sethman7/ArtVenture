// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/AVGameMode.h"
//#include "UObject/ConstructorHelpers.h"
//#include "Engine/World.h"

AAVGameMode::AAVGameMode()
{
	

	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Game/ArtVenture/Blueprint/Player/BP_Player.BP_Player_C"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FObjectFinder<UBlueprint> PlayerControllerBPRef(TEXT("/Script/ArtVenture.AVPlayerController"));
	if (PlayerControllerBPRef.Object)
	{
		PlayerControllerClass = (UClass*)PlayerControllerBPRef.Object->GeneratedClass;
	}
}


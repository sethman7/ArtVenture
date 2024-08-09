// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/AVRideableObjectTest.h"
#include "AI/AVRideableAIController.h"
// Sets default values
AAVRideableObjectTest::AAVRideableObjectTest()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AIControllerClass = AAVRideableAIController::StaticClass();
}

// Called when the game starts or when spawned
void AAVRideableObjectTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAVRideableObjectTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAVRideableObjectTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


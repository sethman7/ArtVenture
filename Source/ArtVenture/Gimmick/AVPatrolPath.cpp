// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/AVPatrolPath.h"

// Sets default values
AAVPatrolPath::AAVPatrolPath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	idx = 0;
}

// Called when the game starts or when spawned
void AAVPatrolPath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAVPatrolPath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


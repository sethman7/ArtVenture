// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/AVTeleportableObject.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAVTeleportableObject::AAVTeleportableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AAVTeleportableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAVTeleportableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAVTeleportableObject::Teleport()
{
	UGameplayStatics::OpenLevel(GetWorld(),WorldName);
}

void AAVTeleportableObject::Interact()
{
	Teleport();
}



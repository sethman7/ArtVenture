// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/AVArtPiece.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAVArtPiece::AAVArtPiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Drawing"));

	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AAVArtPiece::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAVArtPiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAVArtPiece::Teleport()
{
	UGameplayStatics::OpenLevel(GetWorld(),WorldName);
	//플레이어 순간이동 
}

FName AAVArtPiece::GetWorldName()
{
	return WorldName;
}



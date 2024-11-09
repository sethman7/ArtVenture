// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/AVTeleportableObject.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
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

void AAVTeleportableObject::Interact()
{
	//다른 레벨로 이동시, 그 레벨에서의 정보들을 어떻게 이곳에서 가져올지 문제임.
	//이동 직전에 다음 레벨의 정보가 필요하기에 알 수가 없음. 
	//싱글톤 사용하기
	UGameplayStatics::OpenLevel(GetWorld(), DestinationWorldName);

}





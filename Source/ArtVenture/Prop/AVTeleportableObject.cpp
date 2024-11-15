//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Prop/AVTeleportableObject.h"
//#include "Kismet/GameplayStatics.h"
//#include "GameFramework/PlayerStart.h"
//#include "GameFramework/Character.h"
//
//
//// Sets default values
//AAVTeleportableObject::AAVTeleportableObject()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
//	RootComponent = Mesh; 
//
//}
//
//// Called when the game starts or when spawned
//void AAVTeleportableObject::BeginPlay()
//{
//	Super::BeginPlay();
//	
//}
//
//// Called every frame
//void AAVTeleportableObject::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//void AAVTeleportableObject::Interact()
//{
//	FString name1 = GetLevel()->GetName();
//	CurrentWorldName = GetWorld()->GetName();
//	UGameplayStatics::OpenLevel(GetWorld(), WorldName);
//	if (CurrentWorldName == "lobbyLevel") return;
//	SpawnPlayer();
//	//FTimerHandle TimerHandle;
//	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AAVTeleportableObject::SpawnPlayer, 3.0f, false);
//}
//
//void AAVTeleportableObject::SpawnPlayer()
//{
//	TArray<AActor*> PlayerStarts;
//	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStarts);
//	AActor* SelectedPlayerStart = nullptr;
//	for (AActor* PlayerStart : PlayerStarts)
//	{
//		if (PlayerStart->GetName() == CurrentWorldName)
//		{
//			SelectedPlayerStart = PlayerStart;
//			break;
//		}
//	}
//
//	if (SelectedPlayerStart == nullptr) return;
//	FVector SpawnLocation = SelectedPlayerStart->GetActorLocation();
//	FRotator SpawnRotation = SelectedPlayerStart->GetActorRotation();
//
//	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
//	ensure(PlayerController);
//	GetWorld()->SpawnActor<ACharacter>(PlayerController->GetOwner()->GetClass(), SpawnLocation, SpawnRotation);
//
//}
//
//
//
//

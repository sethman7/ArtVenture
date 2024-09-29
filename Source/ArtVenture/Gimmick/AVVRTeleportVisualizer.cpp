//// Fill out your copyright notice in the Description page of Project Settings.
//
//
//#include "Gimmick/AVVRTeleportVisualizer.h"
//#include "NiagaraComponent.h"
//#include "Kismet/GameplayStatics.h"
//#include "HeadMountedDisplayFunctionLibrary.h"
//#include "Kismet/KismetMathLibrary.h"
//
//// Sets default values
//AAVVRTeleportVisualizer::AAVVRTeleportVisualizer()
//{
// 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
//	PrimaryActorTick.bCanEverTick = true;
//	TeleportRing = CreateDefaultSubobject<UNiagaraComponent>(TEXT("TeleportRing"));
//	PlayAreaBound = CreateDefaultSubobject<UNiagaraComponent>(TEXT("PlayAreaBound"));
//
//
//	TeleportRing->SetupAttachment(RootComponent);
//	PlayAreaBound->SetupAttachment(RootComponent);
//}
//
//// Called when the game starts or when spawned
//void AAVVRTeleportVisualizer::BeginPlay()
//{
//	Super::BeginPlay();
//	FVector2D vector2d = UHeadMountedDisplayFunctionLibrary::GetPlayAreaBounds(EHMDTrackingOrigin::Stage);
//	PlayAreaBound->SetNiagaraVariableVec3("User.PlayAreaBounds", FVector(vector2d.X, vector2d.Y, 0.0f)); 
//	Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
//	ensure(Player);
//	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
//	ensure(CameraManager);
//}
//
//// Called every frame
//void AAVVRTeleportVisualizer::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//	//PlayAreaBound->SetRelativeLocation();
//	
//
//	FTransform PlayerTransform = Player->GetActorTransform();
//	FVector CameraLocation = CameraManager->GetCameraLocation();
//	
//	FVector InverseTransformLocation = UKismetMathLibrary::InverseTransformLocation(PlayerTransform, CameraLocation);
//	FVector NegateVector = UKismetMathLibrary::NegateVector(InverseTransformLocation);
//	PlayAreaBound->SetRelativeLocation(FVector(NegateVector.X, NegateVector.Y, 0.0f));
//
//	FRotator PlayerRotator = Player->GetActorRotation();
//	SetActorRotation(PlayerRotator);
//}
//

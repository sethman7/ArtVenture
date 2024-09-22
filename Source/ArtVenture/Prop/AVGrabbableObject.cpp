// Fill out your copyright notice in the Description page of Project Settings.


#include "Prop/AVGrabbableObject.h"
#include "Components/SphereComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAVGrabbableObject::AAVGrabbableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("LiquidBall"));
	//RootComponent = SphereComponent;
	//SphereComponent->InitSphereRadius(40.0f);
	//SphereComponent->SetCollisionProfileName(TEXT("Pawn"));
	//SphereComponent->SetWorldScale3D(FVector(1.0f, 1.0f, 1.0f));


	//SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	//SphereVisual->SetupAttachment(RootComponent);
	//static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	//if (SphereVisualAsset.Succeeded())
	//{
	//	SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
	//	SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.0f));
	//	SphereVisual->SetWorldScale3D(FVector(0.8f));
	//}


}

// Called when the game starts or when spawned
void AAVGrabbableObject::BeginPlay()
{
	Super::BeginPlay();
	//OwnerMaterial = SphereVisual->GetMaterial(0);
	
}

// Called every frame
void AAVGrabbableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAVGrabbableObject::Interact()
{
	IsGrabbale = true;
}

//void AAVGrabbableObject::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
//{
//	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
//	if (! ( Hit.IsValidBlockingHit() && OtherComp->GetCollisionProfileName()=="Drawable") )
//	{
//		return;
//	}
//
//	OtherComp->SetMaterial(0, OwnerMaterial);
//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, TEXT("HIT"));
//	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DestoryParticle, GetActorLocation(), GetActorRotation(), FVector(2.0f));
//	DestoryFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DestoryFX, FVector(GetActorLocation()), GetActorRotation(), FVector(5.0f));
//
//	if (DestoryFXComponent)
//	{
//		DestoryFXComponent->Activate();
//	}
//	
//	Destroy();
//
//}

void AAVGrabbableObject::ChangeMaterial()
{

}




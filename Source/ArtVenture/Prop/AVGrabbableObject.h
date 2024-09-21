// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/AVInteractableInterface.h"
#include "AVGrabbableObject.generated.h"

UCLASS()
class ARTVENTURE_API AAVGrabbableObject : public AActor, public IAVInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAVGrabbableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact() override;

	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, 
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	void ChangeMaterial();

	UPROPERTY(EditAnywhere)
	class USphereComponent* SphereComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* SphereVisual;

	UPROPERTY(EditAnywhere, Category = Effect)
	class UNiagaraSystem* DestoryFX;

	class UNiagaraComponent* DestoryFXComponent;

private:
	class UMaterialInterface* OwnerMaterial;
};

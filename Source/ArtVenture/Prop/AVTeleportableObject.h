// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/AVInteractableInterface.h"
#include "AVTeleportableObject.generated.h"

UCLASS(Abstract)
class ARTVENTURE_API AAVTeleportableObject : public AActor, public IAVInteractableInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAVTeleportableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Mesh)
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportable") // 블프로 WorldName값이 필요해서 수정햇서
	FName DestinationWorldName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleportable")
	FString CurrentWorldName;



	UFUNCTION(BlueprintCallable)
	virtual void Interact() override;
};

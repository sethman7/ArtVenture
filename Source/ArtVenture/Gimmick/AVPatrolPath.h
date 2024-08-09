// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AVPatrolPath.generated.h"

UCLASS()
class ARTVENTURE_API AAVPatrolPath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAVPatrolPath();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PatrolLocation, Meta = (MakeEditWidget = true))
	TArray<FVector> PatrolPoints;
	int idx;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

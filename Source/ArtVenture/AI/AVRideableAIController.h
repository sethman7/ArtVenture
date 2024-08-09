// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AVRideableAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARTVENTURE_API AAVRideableAIController : public AAIController
{
	GENERATED_BODY()
public:
	AAVRideableAIController();
	virtual void OnPossess(APawn* InPawn) override;
	void RunAI();
	void StopAI();

	void SetBB_PatrolLoc(FVector vector);
	FVector GetBB_PatrolLoc();

	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;
	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;
};

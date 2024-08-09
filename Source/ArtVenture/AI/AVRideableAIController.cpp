// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AVRideableAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

AAVRideableAIController::AAVRideableAIController()
{
	//BB,BT 
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/ArtVenture/RideableObject/BB_RideableObject.BB_RideableObject"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}
	ensure(BBAssetRef.Object);


	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/ArtVenture/RideableObject/BT_RideableObject.BT_RideableObject"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
	ensure(BTAssetRef.Object);
}

void AAVRideableAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn); 
	RunAI();
}

void AAVRideableAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (!UseBlackboard(BBAsset, BlackboardPtr)) { return; }
	RunBehaviorTree(BTAsset);
}

void AAVRideableAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AAVRideableAIController::SetBB_PatrolLoc(FVector vector)
{
	GetBlackboardComponent()->SetValueAsVector(TEXT("PatrolLoc"), vector);
}

FVector AAVRideableAIController::GetBB_PatrolLoc()
{
	return GetBlackboardComponent()->GetValueAsVector(TEXT("PatrolLoc"));
}

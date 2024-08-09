// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolLocation.h"
#include "Prop/AVRideableObjectTest.h"
#include "AI/AVRideableAIController.h"
#include "Gimmick/AVPatrolPath.h"

UBTTask_FindPatrolLocation::UBTTask_FindPatrolLocation()
{
	NodeName = TEXT("FindPatrolLocation");
}

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AAVRideableObjectTest* RideableObject = Cast<AAVRideableObjectTest>(ControllingPawn);
	ensure(RideableObject);
	AAVPatrolPath* PatrolpathActor = Cast<AAVPatrolPath>(RideableObject->PatrolPath);
	ensure(PatrolpathActor);
	AAVRideableAIController* AI = Cast<AAVRideableAIController>(ControllingPawn->GetController());

	TArray<FVector> PArray = PatrolpathActor->PatrolPoints;
	int length = PArray.Num() - 1;
	if (PatrolpathActor->idx <= length)
	{
		AI->SetBB_PatrolLoc(PArray[PatrolpathActor->idx]);
		PatrolpathActor->idx += 1;
	}
	else
	{
		PatrolpathActor->idx = 0;
	}
	return EBTNodeResult::Succeeded;
}

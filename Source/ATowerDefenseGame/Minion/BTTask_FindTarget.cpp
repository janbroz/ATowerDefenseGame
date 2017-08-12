// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "BTTask_FindTarget.h"
#include "MinionController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Helpers/TDTargetPoint.h"


EBTNodeResult::Type UBTTask_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMinionController* MController = Cast<AMinionController>(OwnerComp.GetOwner());
	if (MController != nullptr && MController->GetMinionBlackboardComponent())
	{
		int32 SearchIndex = MController->GetMinionBlackboardComponent()->GetValueAsInt(TEXT("RouteIndex"));

		for (TActorIterator<ATDTargetPoint> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			ATDTargetPoint* TargetPoint = *ActorItr;
			if (SearchIndex == TargetPoint->RouteIndex)
			{
				MController->GetMinionBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), TargetPoint);
				break;
			}
		}
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}

	
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "BTTask_GetNextRouteIndex.h"
#include "MinionController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Helpers/TDTargetPoint.h"


EBTNodeResult::Type UBTTask_GetNextRouteIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMinionController* MController = Cast<AMinionController>(OwnerComp.GetOwner());
	if (MController != nullptr)
	{
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Change the target naw"));
		}*/
	}

	return EBTNodeResult::Succeeded;
}

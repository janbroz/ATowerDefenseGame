// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "MinionController.h"
#include "TowerMinion.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AMinionController::AMinionController()
{
	MinionBehavior = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));
	MinionBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));

}


void AMinionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMinionController::Possess(APawn* MinionPawn)
{
	Super::Possess(MinionPawn);

	ATowerMinion* Minion = Cast<ATowerMinion>(GetPawn());
	if (Minion && Minion->BehaviorTree)
	{
		if (Minion->BehaviorTree->BlackboardAsset)
		{
			MinionBlackboard->InitializeBlackboard(*(Minion->BehaviorTree->BlackboardAsset));
			MinionBehavior->StartTree(*Minion->BehaviorTree);
		}
	}

}

UBlackboardComponent* AMinionController::GetMinionBlackboardComponent()
{
	return MinionBlackboard;
}
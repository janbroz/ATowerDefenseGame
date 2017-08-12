// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MinionController.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API AMinionController : public AAIController
{
	GENERATED_BODY()
public:
	AMinionController();
	
protected:

public:
	// The tree of life
	class UBehaviorTreeComponent* MinionBehavior;
	// The blackboard comp
	UBlackboardComponent* MinionBlackboard;

private:
	virtual void Tick(float DeltaTime) override;
	virtual void Possess(APawn* MinionPawn) override;

public:
	class UBlackboardComponent* GetMinionBlackboardComponent();
};

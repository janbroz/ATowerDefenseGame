// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TowerGameState.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API ATowerGameState : public AGameState
{
	GENERATED_BODY()
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

public:
	ATowerGameState();

	
	
};

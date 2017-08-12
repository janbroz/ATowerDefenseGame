// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "ATowerDefenseGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API AATowerDefenseGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
protected:
	virtual void Tick(float DeltaTime) override;

public:
	AATowerDefenseGameGameModeBase();
	
	
};

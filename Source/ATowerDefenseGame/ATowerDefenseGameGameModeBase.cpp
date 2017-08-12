// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "ATowerDefenseGameGameModeBase.h"
#include "Player/TowerPlayerController.h"
#include "Player/TowerPawn.h"
#include "TowerDefenseGameState.h"
#include "TowerGameState.h"

AATowerDefenseGameGameModeBase::AATowerDefenseGameGameModeBase()
{
	PlayerControllerClass = ATowerPlayerController::StaticClass();
	DefaultPawnClass = ATowerPawn::StaticClass();
	GameStateClass = ATowerDefenseGameState::StaticClass();
	//GameStateClass = ATowerGameState::StaticClass();
}

void AATowerDefenseGameGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("upsis"));
	}
}
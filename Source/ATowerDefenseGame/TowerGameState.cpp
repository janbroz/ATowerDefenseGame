// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerGameState.h"



ATowerGameState::ATowerGameState()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

}


void ATowerGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("upsis"));
	}
}

void ATowerGameState::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("upsis"));
	}
}
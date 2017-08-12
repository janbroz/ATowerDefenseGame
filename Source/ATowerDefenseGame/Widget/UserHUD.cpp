// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "UserHUD.h"
#include "GlobalEventHandler.h"
#include "TowerDefenseGameState.h"


UUserHUD::UUserHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
}


void UUserHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ATowerDefenseGameState* TDGameState = Cast<ATowerDefenseGameState>(GetWorld()->GetGameState());
	if (TDGameState)
	{
		EventHandler = TDGameState->EventHandler;
	}

	if (EventHandler)
	{
		EventHandler->OnWaveSpawned.AddDynamic(this, &UUserHUD::UpdateWaveHandler);
		EventHandler->OnUpdateMinionAmount.AddDynamic(this, &UUserHUD::UpdateMinionAmount);
	}
	if (GEngine && EventHandler)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Build was ok"));
	}
}

void UUserHUD::SetupDisplayMode(EDisplayMode DisplayMode)
{
	if (HUDDisplayMode == DisplayMode)
	{
		HUDDisplayMode = EDisplayMode::NONE;
	}
	else
	{
		HUDDisplayMode = DisplayMode;
	}
}


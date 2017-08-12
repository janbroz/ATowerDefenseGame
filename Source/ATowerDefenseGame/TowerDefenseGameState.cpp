// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerDefenseGameState.h"
#include "Minion/EnemySpawner.h"
#include "Minion/TowerMinion.h"
#include "GlobalEventHandler.h"

ATowerDefenseGameState::ATowerDefenseGameState()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	CurrentWave = 0;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
	bWaveFullySpawned = false;
	bReadyForNextWave = false;
	TimeBetweenWaves = 10.f;
}

void ATowerDefenseGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RealSeconds = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	TimeSpan = FTimespan(/*Hours*/0,/*Minutes*/0, RealSeconds /*Seconds*/);

}

void ATowerDefenseGameState::BeginPlay()
{
	Super::BeginPlay();
	
	EventHandler->OnMinionKilled.AddDynamic(this, &ATowerDefenseGameState::OnMinionKilledHandler);
	EventHandler->OnBeginWave.AddDynamic(this, &ATowerDefenseGameState::OnBeginWaveHandler);
	EventHandler->OnFullySpawnedWave.AddDynamic(this, &ATowerDefenseGameState::OnFullySpawnedWaveHandler);
	SetupSpawner();
	BeginWaves();
}

void ATowerDefenseGameState::SetupSpawner()
{
	TArray<AActor*> Spawners;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), Spawners);

	if (Spawners.Num() > 0)
	{
		EnemySpawner = Cast<AEnemySpawner>(Spawners[0]);
	}
}

void ATowerDefenseGameState::BeginWaves()
{
	if (EnemySpawner)
	{
		EnemySpawner->EnemySpawned.BindUFunction(this, FName("RespondToSpawn"));

		EnemySpawner->SetCurrentWave(CurrentWave);
		EventHandler->OnWaveSpawned.Broadcast(CurrentWave);
		//EventHandler->OnUpdateMinionAmount.Broadcast(EnemiesAlive, EnemiesSpawned);
		EnemySpawner->SpawnWave();
	}

}

void ATowerDefenseGameState::RespondToSpawn(int32 Amount)
{
	EnemiesSpawned = Amount;
}

void ATowerDefenseGameState::RecieveMessage(float PName)
{


}

void ATowerDefenseGameState::OnMinionKilledHandler(FString MinionName)
{
	EnemiesAlive--;
	EventHandler->OnUpdateMinionAmount.Broadcast(EnemiesAlive, EnemiesPerWave);

	if (EnemiesAlive <= 0)
	{
		bReadyForNextWave = true;
		CurrentWave++;
		// Wave is done for
		FTimerHandle FreeTime;
		GetWorldTimerManager().SetTimer(FreeTime, this, &ATowerDefenseGameState::BeginWaves, TimeBetweenWaves, false);
	}
}

void ATowerDefenseGameState::OnBeginWaveHandler(uint8 AliveAmount)
{
	EnemiesAlive = AliveAmount;
	EnemiesPerWave = AliveAmount;
	EventHandler->OnUpdateMinionAmount.Broadcast(EnemiesAlive, EnemiesAlive);
}

void ATowerDefenseGameState::OnFullySpawnedWaveHandler()
{
	bWaveFullySpawned = true;
	
}
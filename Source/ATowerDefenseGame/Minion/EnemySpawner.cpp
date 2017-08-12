// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "EnemySpawner.h"
#include "TowerMinion.h"
#include "MinionController.h"
#include "GlobalEventHandler.h"
#include "TowerDefenseGameState.h"
// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
	SpawnOffset = 150;
	SpawnRate = 0.5f;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	ATowerDefenseGameState* TDGameState = Cast<ATowerDefenseGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (TDGameState)
	{
		EventHandler = TDGameState->EventHandler;
	}


	//SpawnWave();
}



// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnWave()
{
	// This means the wave just started
	if (EnemiesSpawned <= 0)
	{
		bNewWave = true;

		ATowerDefenseGameState* TDGameState = Cast<ATowerDefenseGameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (TDGameState)
		{
			TDGameState->EventHandler->OnBeginWave.Broadcast(EnemiesToSpawn);
		}		
	}

	if (MinionClasses.IsValidIndex(CurrentWave) && EnemiesSpawned < EnemiesToSpawn)
	{
		FActorSpawnParameters FASP;
		const FVector SpawnerLocation = GetActorLocation();
		const FRotator SpawnerRotation = GetActorRotation();
		auto Minion = GetWorld()->SpawnActor<ATowerMinion>(MinionClasses[CurrentWave], SpawnerLocation, SpawnerRotation, FASP);
		if (Minion != nullptr)
		{
			EnemiesSpawned++;

			EnemySpawned.Execute(EnemiesSpawned);
		}
	}

	if (EnemiesSpawned < EnemiesToSpawn)
	{
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AEnemySpawner::SpawnWave, SpawnRate, false);
	}

	if (EnemiesSpawned >= EnemiesToSpawn)
	{
		ATowerDefenseGameState* TDGameState = Cast<ATowerDefenseGameState>(UGameplayStatics::GetGameState(GetWorld()));
		if (TDGameState)
		{
			TDGameState->EventHandler->OnFullySpawnedWave.Broadcast();
		}
	}
}

FVector AEnemySpawner::GetRandomLocation(FVector OldLocation)
{
	float XOffset = FMath::FRandRange(-SpawnOffset, SpawnOffset);
	float YOffset = FMath::FRandRange(-SpawnOffset, SpawnOffset);
	float NewX = OldLocation.X + XOffset;
	float NewY = OldLocation.Y + YOffset;
	return FVector(NewX, NewY, OldLocation.Z);
}

void AEnemySpawner::SetCurrentWave(int32 NewWave)
{
	CurrentWave = NewWave;
	EnemiesSpawned = 0;
	if (CurrentWave > 0)
	{
		EnemiesToSpawn += 2;
		
	}
	
}


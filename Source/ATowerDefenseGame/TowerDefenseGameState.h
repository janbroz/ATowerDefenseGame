// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TowerDefenseGameState.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API ATowerDefenseGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

public:
	ATowerDefenseGameState();
	
	void SetupSpawner();
	void BeginWaves();

	UFUNCTION()
		void RespondToSpawn(int32 Amount);
	UFUNCTION()
		void RecieveMessage(float PName);
	UFUNCTION()
		void OnMinionKilledHandler(FString MinionName);
	UFUNCTION()
		void OnBeginWaveHandler(uint8 AliveAmount);
	UFUNCTION()
		void OnFullySpawnedWaveHandler();

public:
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		float RealSeconds;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		FTimespan TimeSpan;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		int32 CurrentWave;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		class AEnemySpawner* EnemySpawner;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		int32 EnemiesSpawned;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		int32 EnemiesPerWave;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		int32 EnemiesAlive;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		uint32 bWaveFullySpawned : 1;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		uint32 bReadyForNextWave : 1;
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		int32 TimeBetweenWaves;
};

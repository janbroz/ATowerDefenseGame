// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class ATOWERDEFENSEGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:
	FVector GetRandomLocation(FVector OldLocation);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		TArray<TSubclassOf<class ATowerMinion>> MinionClasses;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int32 EnemiesToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int32 EnemiesSpawned;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int32 EnemiesAlive;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int32 CurrentWave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int32 SpawnOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		float SpawnRate;
	UPROPERTY(EditAnywhere, Category = "Event Manager")
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		uint32 bNewWave : 1;

public:
	UFUNCTION()
		void SpawnWave();
	UFUNCTION()
		void SetCurrentWave(int32 NewWave);

	DECLARE_DELEGATE_OneParam(FSaySpawned, int32);
	FSaySpawned EnemySpawned;


};

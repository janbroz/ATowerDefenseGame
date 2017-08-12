// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GlobalEventHandler.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaveDelegate_OnWaveSpawned, uint8, WaveIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMinionDelegate_OnMinionKilled, FString, MinionName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaveDelegate_OnBeginWave, uint8, AliveAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaveDelegate_OnFullySpawnedWave);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FWaveDelegate_OnUpdateMinionAmount, uint8, Alive, uint8, Max);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATOWERDEFENSEGAME_API UGlobalEventHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGlobalEventHandler();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave events")
		FWaveDelegate_OnWaveSpawned OnWaveSpawned;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave events")
		FMinionDelegate_OnMinionKilled OnMinionKilled;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave events")
		FWaveDelegate_OnBeginWave OnBeginWave;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave events")
		FWaveDelegate_OnFullySpawnedWave OnFullySpawnedWave;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Wave events")
		FWaveDelegate_OnUpdateMinionAmount OnUpdateMinionAmount;

};

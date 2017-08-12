// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoTManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ATOWERDEFENSEGAME_API UDoTManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoTManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
public:
	// With this one we dont have to make a cast to TowerMinion each time we need a reference
	// to the dot manager owner.
	UPROPERTY(VisibleAnywhere, Category = "Dot manager information")
		class ATowerMinion* Minion;
	UPROPERTY(VisibleAnywhere, Category = "Dot manager information")
		FTimerHandle DotTimer;
	UPROPERTY(VisibleAnywhere, Category = "Dot manager information")
		int32 DotIndex;


public:
	UFUNCTION()
		void DamageMinion(AActor* Instigator, float TickFrequency, float Damage);
	UFUNCTION()
		void SetupDamage(AActor* Instigator, float TickFrequency, float Damage);

};

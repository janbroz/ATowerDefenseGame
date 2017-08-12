// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/AbilitySystemInterface.h"
#include "TowerMinion.generated.h"



class UAbilitySystemComponent;
UCLASS()
class ATOWERDEFENSEGAME_API ATowerMinion : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATowerMinion();

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Override that pesky ability system interface stuff
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// more interface stuff
	virtual void SayHello() const override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Minion gets hurt
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

	// Minion has reached his destiny, tell the player he is fucked.
	void FinishedObjective();
	UFUNCTION(BlueprintCallable)
	void TakeDamage2();
	
	UFUNCTION(Category= "Information")
		class UDoTManager* GetDotManager();


public:
	UPROPERTY(EditAnywhere, Category = "Stats")
		UAbilitySystemComponent* AbilitySystem;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float MaxHealth;
	UPROPERTY(EditAnywhere, Category = "Stats")
		float CurrentHealth;
	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 BountyGold;
	UPROPERTY(EditAnywhere, Category = "Stats")
		int32 BountyWood;

public:
	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviorTree;
	UPROPERTY(EditAnywhere, Category = "Event Manager")
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(VisibleAnywhere, Category = "Event Manager")
		class UDoTManager* DotManager;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		float Fuck;
	
};

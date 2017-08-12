// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerData.h"
#include "Ability.generated.h"

UCLASS()
class ATOWERDEFENSEGAME_API AAbility : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAbility();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Use the ability
	UFUNCTION(BlueprintCallable)
		virtual TArray<FAbilityEffect> UseAbility(AActor* Target);
	
	
public:
	


public:
	UPROPERTY(EditAnywhere, Category = "Ability information")
		TArray<FAbilityEffect> AbilityEffects;

	UPROPERTY(EditAnywhere, Category = "Ability information")
		FString AbilityName;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		UTexture2D* AbilityImage;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		ESkillType AbilityType;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		uint32 bHasCooldown : 1;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		uint32 bIsActive : 1;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		float Multiplier;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		float Cooldown;
	UPROPERTY(EditAnywhere, Category = "Ability information")
		AActor* AbilityOwner;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Helpers/Ability.h"
#include "CriticalDamage.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API ACriticalDamage : public AAbility
{
	GENERATED_BODY()
public:
	ACriticalDamage();
	virtual TArray<FAbilityEffect> UseAbility(AActor* Target) override;


	
};

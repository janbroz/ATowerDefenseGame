// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "CriticalDamage.h"




ACriticalDamage::ACriticalDamage()
{
	AbilityName = "Critical damage";
}

TArray<FAbilityEffect> ACriticalDamage::UseAbility(AActor* Target)
{
	//Super::UseAbility(Target);

	return AbilityEffects;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerDataFunctionLibrary.h"

UTowerDataFunctionLibrary::UTowerDataFunctionLibrary(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

UTowerData* UTowerDataFunctionLibrary::GetTowerData(bool& IsValid)
{
	IsValid = false;
	UTowerData* DataInstance = Cast<UTowerData>(GEngine->GameSingleton);

	if (!DataInstance)
	{
		return NULL;
	}
	if (!DataInstance->IsValidLowLevel())
	{
		return NULL;
	}

	IsValid = true;
	return DataInstance;
}

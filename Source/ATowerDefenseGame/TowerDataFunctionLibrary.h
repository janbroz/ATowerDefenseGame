// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TowerData.h"
#include "TowerDataFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API UTowerDataFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UTowerDataFunctionLibrary(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintPure, Category = "Tower data singleton")
		static UTowerData* GetTowerData(bool& IsValid);
	
};

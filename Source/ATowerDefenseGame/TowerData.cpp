// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerData.h"


UTowerData::UTowerData()
{
	TestValue = 42;

	static ConstructorHelpers::FObjectFinder<UDataTable> TowerLookupTable_BP(TEXT("DataTable'/Game/Data/TowerInformation.TowerInformation'"));
	if (TowerLookupTable_BP.Object)
	{
		TowersTable = TowerLookupTable_BP.Object;
	}


}



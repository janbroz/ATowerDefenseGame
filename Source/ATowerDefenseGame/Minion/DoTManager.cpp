// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "DoTManager.h"
#include "TowerMinion.h"

// Sets default values for this component's properties
UDoTManager::UDoTManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoTManager::BeginPlay()
{
	Super::BeginPlay();

	Minion = Cast<ATowerMinion>(GetOwner());
	DotIndex = 0;
	// ...
	
}


// Called every frame
void UDoTManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



void UDoTManager::DamageMinion(AActor* Instigator, float TickFrequency, float Damage)
{
	if (DotIndex < 5)
	{
		const FDamageEvent DotDamage;
		Minion->TakeDamage(1.f, DotDamage, GetWorld()->GetFirstPlayerController(), Instigator);
		DotIndex++;
	}
	else
	{
		Minion->GetWorldTimerManager().ClearTimer(DotTimer);
	}

	
}

void UDoTManager::SetupDamage(AActor* Instigator, float TickFrequency, float Damage)
{
	DotIndex = 0;
	FTimerDelegate DoTDelgate;
	DoTDelgate.BindUFunction(this, FName("DamageMinion"), Instigator, TickFrequency, Damage);
	if (Minion)
	{
		Minion->GetWorldTimerManager().SetTimer(DotTimer, DoTDelgate, TickFrequency, true);
	}
	
}
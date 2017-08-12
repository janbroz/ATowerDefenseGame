// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerMinion.h"
#include "MinionController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "TowerDefenseGameState.h"
#include "GlobalEventHandler.h"
#include "Player/TowerPlayerController.h"
#include "DotManager.h"

// Sets default values
ATowerMinion::ATowerMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AMinionController::StaticClass();
	EventHandler = CreateDefaultSubobject<UGlobalEventHandler>(TEXT("Event handler"));
	DotManager = CreateDefaultSubobject<UDoTManager>(TEXT("Dot manager"));

	MaxHealth = 100.f;
	CurrentHealth = MaxHealth;
	BountyGold = 5;
	BountyWood = 0;
}

// Called when the game starts or when spawned
void ATowerMinion::BeginPlay()
{
	Super::BeginPlay();
	
	ATowerDefenseGameState* TDGameState = Cast<ATowerDefenseGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (TDGameState)
	{
		EventHandler = TDGameState->EventHandler;
	}
	//DeadMessage.AddDynamic(this, &ATowerDefenseGameState::RecieveMessage);
}

// Called every frame
void ATowerMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATowerMinion::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATowerMinion::TakeDamage2()
{
	/*ATowerDefenseGameState* TDGameState = Cast<ATowerDefenseGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (TDGameState)
	{
		TDGameState->EventHandler->OnMinionKilled.Broadcast(TEXT("Holi"));
	}*/

	EventHandler->OnMinionKilled.Broadcast(GetName());
	Destroy();
}

float ATowerMinion::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	const float NewHealth = CurrentHealth - Damage;
	CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	if (CurrentHealth <= 0)
	{
		ATowerPlayerController* Pc = Cast<ATowerPlayerController>(EventInstigator);
		if (Pc)
		{
			Pc->GainResources(BountyGold, BountyWood);
		}
		EventHandler->OnMinionKilled.Broadcast(GetName());
		Destroy();
	}
	return ActualDamage;
}

UDoTManager* ATowerMinion::GetDotManager()
{
	return DotManager;
}

UAbilitySystemComponent* ATowerMinion::GetAbilitySystemComponent() const
{
	return AbilitySystem;
}

void ATowerMinion::SayHello() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Holi, soy de la interface"));
	}
}

void ATowerMinion::FinishedObjective()
{
	ATowerPlayerController* Pc = Cast<ATowerPlayerController>(GetWorld()->GetFirstPlayerController());
	if (Pc)
	{
		// Player loses one live.
		Pc->UpdateLives(-1);
	}
}
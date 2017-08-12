// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "Tower.h"
#include "Minion/TowerMinion.h"
#include "Player/TowerPlayerController.h"
#include "Minion/DoTManager.h"
#include "Helpers/Ability.h"
#include "Projectile.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TowerPlacement = CreateDefaultSubobject<USceneComponent>(TEXT("Tower placement"));
	RootComponent = TowerPlacement;

	PlacementBox = CreateDefaultSubobject<UBoxComponent>(TEXT("PlacementBox"));
	PlacementBox->SetupAttachment(RootComponent);
	PlacementBox->SetBoxExtent(FVector(49.f, 49.f, 49.f));
	PlacementBox->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnBoxBeginOverlap);
	PlacementBox->OnComponentEndOverlap.AddDynamic(this, &ATower::OnBoxEndOverlap);

	TowerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerBase"));
	TowerBase->SetupAttachment(RootComponent);

	TowerHead = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerHead"));
	TowerHead->SetupAttachment(TowerBase);

	TowerCanon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerCanon"));
	TowerCanon->SetupAttachment(TowerHead);

	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile location"));
	ProjectileSpawnLocation->SetupAttachment(TowerCanon);

	Level = 1;
	Range = 600.f;
	Damage = 10.f;
	Speed = 1.f;
	bCanAttack = true;
	bHasProjectileAttack = false;
	Element = EDamageElement::Physical;
	BuildTime = 2.f;
	Cost = 100;

	RangeSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Range sphere"));
	RangeSphere->SetupAttachment(TowerPlacement);
	RangeSphere->SetSphereRadius(Range);
	RangeSphere->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnRangeBeginOverlap);
	RangeSphere->OnComponentEndOverlap.AddDynamic(this, &ATower::OnRangeEndOverlap);

}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = Cast<ATowerPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	UpdateRange();
	SetupAbilities();
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTurret();
}


void ATower::OnRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATowerMinion* Minion = Cast<ATowerMinion>(OtherActor);
	if (Target == nullptr && Minion)
	{
		Target = Minion;
	}
	Attack();
}

void ATower::OnRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ATowerMinion* Minion = Cast<ATowerMinion>(OtherActor);
	if (Target == Minion)
	{
		Target = nullptr;
		TArray<AActor*> OverlappingMinions;
		RangeSphere->GetOverlappingActors(OverlappingMinions, ATowerMinion::StaticClass());
		int8 Amount = OverlappingMinions.Num();

		if (Amount > 0)
		{
			int RandTarget = FMath::RandHelper(Amount - 1);
			Target = Cast<ATowerMinion>(OverlappingMinions[RandTarget]);
		}
		else
		{
			Target = nullptr;
			ResetTurret();
		}
	}
}

void ATower::UpdateRange()
{
	RangeSphere->SetSphereRadius(Range);
}

void ATower::AimTurret()
{
	if (Target)
	{
		FRotator NewRot = (Target->GetActorLocation() - TowerHead->GetComponentLocation()).Rotation();
		TowerHead->SetWorldRotation(NewRot);
	}
}

void ATower::ResetTurret()
{
	TowerHead->SetWorldRotation(FRotator(0.f, 0.f, 0.f));
}

void ATower::Attack()
{
	// Tower attack logic.
	if (bCanAttack && Target)
	{
		AimTurret();

		// Tower should check for passive abilities that modify the attack and apply them to the
		// current attack. Problem is, should we do this every attack or let the ability notify
		// our tower when he is ready?
		UseAbilities();

		IAbilitySystemInterface* AbilityInterface = Cast<IAbilitySystemInterface>(Target);
		if (AbilityInterface)
		{
			AbilityInterface->SayHello();
		}


		if (bHasProjectileAttack && ProjectileClass)
		{
			bCanAttack = false;
			FActorSpawnParameters FASP;
			//AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation->GetComponentLocation(), ProjectileSpawnLocation->GetComponentRotation(), FASP);
			AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, ProjectileSpawnLocation->GetComponentLocation(), ProjectileSpawnLocation->GetComponentRotation());
			if (Projectile && Target)
			{
				Projectile->SetupHoming(Target->GetRootComponent());
				Projectile->SetupDamageFromTower(Damage, Speed, Element, EDamageType::PointDamage, this);
				UGameplayStatics::FinishSpawningActor(Projectile, FTransform(Projectile->GetActorRotation(), Projectile->GetActorLocation()));
			}
			//Projectile->SetupHoming(Target->GetRootComponent());
			GetWorldTimerManager().SetTimer(AttackHandler, this, &ATower::ResetAttack, Speed, false);
		}
		else
		{
			// Insta attack, we have no projectile to spawn.
			bCanAttack = false;
			const FDamageEvent TowerDamage;
			Target->TakeDamage(Damage, TowerDamage, PlayerController, this);

			if (Target && Target->GetDotManager())
			{
				Target->GetDotManager()->SetupDamage(this, 0.5f, 5.f);
			}
			GetWorldTimerManager().SetTimer(AttackHandler, this, &ATower::ResetAttack, Speed, false);
		}
	}
}

void ATower::ResetAttack()
{
	bCanAttack = true;
	Attack();
}

void ATower::SetTowerMode(ETowerMode NewTowerMode)
{
	TowerMode = NewTowerMode;
	switch (NewTowerMode)
	{
	case ETowerMode::Placing:
		RangeSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TowerBase->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TowerHead->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		TowerCanon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		break;
	case ETowerMode::Building:
		BeginBuildTower();
		break;
	case ETowerMode::Enabled:
		RangeSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		break;
	default:
		break;
	}

}

void ATower::BeginBuildTower()
{
	GetWorldTimerManager().SetTimer(BuildTimerHandle, this, &ATower::EndBuildTower, BuildTime);
}

void ATower::EndBuildTower()
{
	SetTowerMode(ETowerMode::Enabled);
}

void ATower::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UBoxComponent* Boxxy = Cast<UBoxComponent>(OtherComp);

	/*if (GEngine && Boxxy)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, Boxxy->GetName());
	}*/
	if (Boxxy)
	{
		bIsOverlappingWhileBuilding = true;
	}

}

void ATower::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("It went out"));
	}*/
	UBoxComponent* Boxxy = Cast<UBoxComponent>(OtherComp);
	if (Boxxy)
	{
		bIsOverlappingWhileBuilding = false;
	}
}

void ATower::SetupAbilities()
{
	for (auto& AbilityClass : AbilityClassList)
	{
		FActorSpawnParameters FASP;
		AAbility* NewAbility = GetWorld()->SpawnActor<AAbility>(FASP);
		if (NewAbility)
		{
			NewAbility->AbilityOwner = this;
			AbilityList.Add(NewAbility);
		}
	}
}

void ATower::UseAbilities()
{
	for (auto& Ability : AbilityList)
	{
		Ability->UseAbility(nullptr);
	}
}

UAbilitySystemComponent* ATower::GetAbilitySystemComponent() const
{

	return AbilitySystem;
}

void ATower::SayHello() const
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, TEXT("Holi, soy de la interface"));
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "Projectile.h"
#include "Minion/TowerMinion.h"
#include "Tower.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	RootComponent = ProjectileCollision;
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnProjectileBeginOverlap);
	ProjectileCollision->OnComponentEndOverlap.AddDynamic(this, &AProjectile::OnProjectileEndOverlap);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile movement"));
	ProjectileMovement->SetUpdatedComponent(ProjectileCollision);
	ProjectileMovement->InitialSpeed = 1200.f;
	

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetupKillSwitch(3.f);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::SetupHoming(USceneComponent* Target)
{
	ProjectileMovement->bIsHomingProjectile = true;
	ProjectileMovement->HomingTargetComponent = Target;
	ProjectileMovement->HomingAccelerationMagnitude = 20000.f;
	ProjectileMovement->MaxSpeed = 1600.f;
}

void AProjectile::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATowerMinion* Minion = Cast<ATowerMinion>(OtherActor);
	if (Minion)
	{
		Minion->TakeDamage(Damage, FDamageEvent::FDamageEvent(), GetWorld()->GetFirstPlayerController(), SpawnedBy);
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Boom"));
		}
		Destroy();
	}
}

void AProjectile::OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void AProjectile::SetupDamageFromTower(float NewDamage, float NewSpeed, EDamageElement Element, EDamageType Type, ATower* TowerInstigator)
{
	Damage = NewDamage;
	Speed = NewSpeed;
	DamageElement = Element;
	DamageType = Type;
	SpawnedBy = TowerInstigator;
}

void AProjectile::SetupKillSwitch(float Time)
{
	GetWorldTimerManager().SetTimer(TtlTimer, this, &AProjectile::DetonateProjectile, Speed, false);

}

void AProjectile::DetonateProjectile()
{
	// We can do additional stuff here like detonate and such.

	Destroy();
}
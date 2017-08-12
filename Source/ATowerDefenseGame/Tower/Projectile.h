// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class ATOWERDEFENSEGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Projectile should only live for 3 secs max;
	void SetupKillSwitch(float Time);

	// cause destroy is a bool ... man.
	void DetonateProjectile();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Setup projectile if homing
	void SetupHoming(USceneComponent* Target);
	// Collide with a target
	UFUNCTION()
		void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// End collision
	UFUNCTION()
		void OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	// Setup projectile information from tower.
	void SetupDamageFromTower(float NewDamage, float NewSpeed, EDamageElement Element, EDamageType Type, class ATower* TowerInstigator);


public:
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		EDamageElement DamageElement;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		EDamageType DamageType;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		float Speed;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		float Damage;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		uint32 Homing;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		UStaticMeshComponent* ProjectileMesh;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		USphereComponent* ProjectileCollision;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		class ATower* SpawnedBy;
	UPROPERTY(VisibleAnywhere, Category = "Projectile information")
		FTimerHandle TtlTimer;
	
};

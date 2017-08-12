// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerData.h"
#include "Abilities/AbilitySystemInterface.h"
#include "Tower.generated.h"


UCLASS()
class ATOWERDEFENSEGAME_API ATower : public AActor, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Implement the ability system interface pure functions
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void SayHello() const override;
	UFUNCTION()
		void OnRangeBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnRangeEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	void UpdateRange();
	void AimTurret();
	void ResetTurret();
	void Attack();
	void ResetAttack();
	void SetTowerMode(ETowerMode NewTowerMode);
	void BeginBuildTower();
	void EndBuildTower();

	// Spawn the abilities assigned to the tower
	void SetupAbilities();
	void UseAbilities();



public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower information")
		USceneComponent* TowerPlacement;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower information")
		USceneComponent* ProjectileSpawnLocation;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower information")
		USphereComponent* RangeSphere;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower information")
		UBoxComponent* PlacementBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Tower information")
		UAbilitySystemComponent* AbilitySystem;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		class ATowerPlayerController* PlayerController;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		TSubclassOf<class AProjectile> ProjectileClass;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		UStaticMeshComponent* TowerBase;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		UStaticMeshComponent* TowerHead;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		UStaticMeshComponent* TowerCanon;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		float Range;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		float Speed;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		float Damage;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		float BuildTime;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		int32 Cost;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		TArray<class ATowerMinion*> EnemiesInRange;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		class ATowerMinion* Target;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		uint32 bCanAttack : 1;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		uint32 bIsOverlappingWhileBuilding :1;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		uint32 bHasProjectileAttack : 1;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		int32 Level;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Tower information")
        EDamageElement Element;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		FTimerHandle BuildTimerHandle;
	UPROPERTY(VisibleAnywhere, Category = "Tower information")
		ETowerMode TowerMode;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		TArray<TSubclassOf<class AAbility>> AbilityClassList;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		TArray<class AAbility*> AbilityList;
	UPROPERTY(EditAnywhere, Category = "Tower information")
		TArray<FAbilityEffect> Modifiers;

	FTimerHandle AttackHandler;
};

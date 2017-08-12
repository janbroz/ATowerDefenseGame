// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "TowerPawn.generated.h"

UCLASS()
class ATOWERDEFENSEGAME_API ATowerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Zoom the player camera.
	void ZoomPlayerCamera(float Amount, float Multiplier);

	// Update the zoom level.
	void UpdateZoomLevel();

	// Get the camera length
	float GetCameraArmLength();
private:
	UPROPERTY(Category = Camera, EditAnywhere)
		class ATowerPlayerController* ThePlayer;
	UPROPERTY(Category = Camera, EditAnywhere)
		USceneComponent* PlayerSoul;
	UPROPERTY(Category = Camera, EditAnywhere)
		USpringArmComponent* CameraArm;
	UPROPERTY(Category = Camera, EditAnywhere)
		UCameraComponent* Camera;
	UPROPERTY(Category = Camera, EditAnywhere)
		float NewCameraLength;
	UPROPERTY(EditDefaultsOnly, Category = Curve)
		UCurveFloat* ZoomCurve;
	UPROPERTY(EditDefaultsOnly, Category = Curve)
		uint32 bZooming : 1;
};

// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerPawn.h"
#include "TowerPlayerController.h"

// Sets default values
ATowerPawn::ATowerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerSoul = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerSoul"));
	RootComponent = PlayerSoul;

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);
	CameraArm->TargetArmLength = 1800.f;
	CameraArm->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraArm->bDoCollisionTest = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraArm, CameraArm->SocketName);

	NewCameraLength = 800.f;

	static ConstructorHelpers::FObjectFinder<UCurveFloat> ZoomCurve_BP(TEXT("Class'/Game/Player/CameraZoom.CameraZoom'"));
	if (ZoomCurve_BP.Object != nullptr)
	{
		ZoomCurve = ZoomCurve_BP.Object;
	}

	bZooming = false;
}

// Called when the game starts or when spawned
void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	ThePlayer = Cast<ATowerPlayerController>(GetController());
}

// Called every frame
void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateZoomLevel();


}

// Called to bind functionality to input
void ATowerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATowerPawn::ZoomPlayerCamera(float Amount, float Multiplier)
{
	NewCameraLength = FMath::Clamp(NewCameraLength + (Amount * Multiplier * (-1.f)), 500.f, 2500.f);
	bZooming = true;
}

void ATowerPawn::UpdateZoomLevel()
{
	if (bZooming)
	{
		float OldCameraLength = CameraArm->TargetArmLength;
		CameraArm->TargetArmLength = FMath::FInterpTo(OldCameraLength, NewCameraLength, GetWorld()->GetDeltaSeconds(), 3.f);

		float CameraLengthDelta = FMath::Abs(CameraArm->TargetArmLength - NewCameraLength);
		if (ThePlayer)
		{
			ThePlayer->CalculateZoomMovMultiplier();
		}
		if (CameraLengthDelta < 1.f)
		{
			bZooming = false;
		}
	}
}

float ATowerPawn::GetCameraArmLength()
{
	return CameraArm->TargetArmLength;
}
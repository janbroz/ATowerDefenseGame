// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TowerPlayerController.h"
#include "TowerPawn.h"
#include "Blueprint/UserWidget.h"
#include "Widget/UserHUD.h"
#include "Minion/TowerMinion.h"
#include "Tower/Tower.h"

ATowerPlayerController::ATowerPlayerController()
{
	bShowMouseCursor = true;
	ZoomMultiplier = 5.f;
	
	Gold = 200;
	Wood = 0;
	Lives = 20;
	SelectedType = ESelectedUnitType::NONE;
	bShowingMainMenu = false;
	static ConstructorHelpers::FObjectFinder<UClass> WidgetBP(TEXT("/Game/UMG/PlayerHUD.PlayerHUD_C"));
	if (WidgetBP.Object)
	{
		PlayerHUDClass = WidgetBP.Object;
	}
	static ConstructorHelpers::FObjectFinder<UClass> PlayerMenuBP(TEXT("/Game/UMG/GameMenu.GameMenu_C"));
	if (PlayerMenuBP.Object)
	{
		PlayerMenuClasss = PlayerMenuBP.Object;
	}
}

void ATowerPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ThePawn = Cast<ATowerPawn>(GetPawn());
	SetInputMode(FInputModeGameAndUI());
	
	if (PlayerHUDClass)
	{
		PlayerHUD = CreateWidget<UUserHUD>(this, PlayerHUDClass);
		if (PlayerHUD)
		{
			PlayerHUD->AddToViewport();
			PlayerHUD->UpdateResources(Gold, Wood);
		}
	}
	if (PlayerMenuClasss)
	{
		PlayerMenu = CreateWidget<UUserWidget>(this, PlayerMenuClasss);
		if (PlayerMenu)
		{
			PlayerMenu->AddToViewport();
			PlayerMenu->SetIsEnabled(false);
			PlayerMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ATowerPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckForActions();
	CheckCameraScroll();

	//GainResources(0, 0);
}

void ATowerPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseButton", EInputEvent::IE_Pressed, this, &ATowerPlayerController::LeftMousePressed);
	InputComponent->BindAction("RightMouseButton", EInputEvent::IE_Pressed, this, &ATowerPlayerController::RightMousePressed);
	InputComponent->BindAction("ToggleBuild", EInputEvent::IE_Pressed, this, &ATowerPlayerController::ToggleBuild);
	InputComponent->BindAction("ToggleMenu", EInputEvent::IE_Pressed, this, &ATowerPlayerController::ToggleMainMenu);

	InputComponent->BindAxis("HorizontalMovement", this, &ATowerPlayerController::HorizontalMovement);
	InputComponent->BindAxis("VerticalMovement", this, &ATowerPlayerController::VerticalMovement);
	InputComponent->BindAxis("ZoomWheel", this, &ATowerPlayerController::ZoomCamera);

}

void ATowerPlayerController::ToggleMainMenu()
{
	bShowingMainMenu = !bShowingMainMenu;

	if (bShowingMainMenu)
	{
		if (PlayerMenu)
		{
			PlayerMenu->SetIsEnabled(true);
			PlayerMenu->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		if (PlayerMenu)
		{
			PlayerMenu->SetIsEnabled(false);
			PlayerMenu->SetVisibility(ESlateVisibility::Hidden);
		}
	}

}

void ATowerPlayerController::CheckForActions()
{
	if (bPlayerIsBuilding && TowerToBuild)
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		if (Hit.Actor != nullptr)
		{
			FVector SnapLocation = SnapCoordinates(Hit.Location);
			TowerToBuild->SetActorLocation(SnapLocation);
			if (Hit.Actor->Tags.Num() > 0 && Hit.GetActor()->Tags[0] == "BuildSupport")
			{
				bValidSurface = true;
			}
			else
			{
				bValidSurface = false;
			}
		}
	}
}

FVector ATowerPlayerController::SnapCoordinates(FVector InitialCoords)
{
	float X, Y;
	X = (int)(InitialCoords.X / 25) * 25;
	Y = (int)(InitialCoords.Y / 25) * 25;
	return FVector(X, Y, InitialCoords.Z);
}

void ATowerPlayerController::LeftMousePressed()
{
	if (bPlayerIsBuilding && TowerToBuild && bValidSurface && !TowerToBuild->bIsOverlappingWhileBuilding)
	{
		TowerToBuild->SetTowerMode(ETowerMode::Building);
		GainResources(-TowerToBuild->Cost, 0);
		TowerToBuild = nullptr;
	}
	else
	{
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, true, Hit);
		if (Hit.Actor != nullptr)
		{
			ATowerMinion* Minion = Cast<ATowerMinion>(Hit.GetActor());
			ATower* Tower = Cast<ATower>(Hit.GetActor());
			if (Minion)
			{
				SelectedUnit = Minion;
				SelectedType = ESelectedUnitType::Minion;
				PlayerHUD->UpdateSelectedActor(SelectedUnit, ESelectedUnitType::Minion);

			}
			if (Tower)
			{
				SelectedUnit = Tower;
				SelectedType = ESelectedUnitType::Building;
			}
		}
	}
}

void ATowerPlayerController::RightMousePressed()
{
	if (bPlayerIsBuilding && TowerToBuild)
	{
		TowerToBuild->Destroy();
		TowerToBuild = nullptr;
	}

	
	SelectedUnit = nullptr;
	PlayerHUD->UpdateSelectedActor(nullptr, ESelectedUnitType::NONE);
	
}

void ATowerPlayerController::ToggleBuild()
{
	bPlayerIsBuilding = !bPlayerIsBuilding;

	if (!bPlayerIsBuilding)
	{
		ClearBuildingTower();
	}
	PlayerHUD->ToggleBuildMode(bPlayerIsBuilding);

}

void ATowerPlayerController::HorizontalMovement(float Amount)
{
	if (Amount != 0.f && ThePawn)
	{
		FVector Offset = ThePawn->GetActorRightVector() * ZoomMultiplier * Amount * 10.f;
		FVector NewLoc = ThePawn->GetActorLocation() + Offset;
		ThePawn->SetActorLocation(NewLoc);
	}
}

void ATowerPlayerController::VerticalMovement(float Amount)
{
	if (Amount != 0.f && ThePawn)
	{
		FVector Offset = ThePawn->GetActorForwardVector() * ZoomMultiplier * Amount * 10.f;
		FVector NewLoc = ThePawn->GetActorLocation() + Offset;
		ThePawn->SetActorLocation(NewLoc);
	}
}

void ATowerPlayerController::ZoomCamera(float Amount)
{
	if (Amount != 0 && ThePawn)
	{
		ThePawn->ZoomPlayerCamera(Amount, 300.f);
	}
}

void ATowerPlayerController::CalculateZoomMovMultiplier()
{
	// True random!
	//ZoomMultiplier = 4.f;

	if (ThePawn)
	{
		const float ArmLength = ThePawn->GetCameraArmLength();
		if (ArmLength < 1000.f)
		{
			ZoomMultiplier = 5.f;
		}
		else if(ArmLength < 1500.f)
		{
			ZoomMultiplier = 10.f;
		}
		else
		{
			ZoomMultiplier = 15.f;
		}
	}
}

void ATowerPlayerController::CheckCameraScroll()
{
	int32 ScreenX, ScreenY;
	float MouseX, MouseY;
	GetViewportSize(ScreenX, ScreenY);
	GetMousePosition(MouseX, MouseY);
	
	float PercX = MouseX / ScreenX;
	float PercY = MouseY / ScreenY;

	if (PercX > 0.989f)
	{
		HorizontalMovement(1.f);
	}
	else if (PercX <  0.025f && PercX >= 0.f)
	{
		HorizontalMovement(-1.f);
	}
	if (PercY > 0.989f)
	{
		VerticalMovement(-1.f);
	}
	else if (PercY <  0.025f && PercY >= 0.f)
	{
		VerticalMovement(1.f);
		/*if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("Move up"));
		}*/
	}

}

void ATowerPlayerController::GainResources(int32 PlusGold, int32 PlusWood)
{
	Gold += PlusGold;
	Wood += PlusWood;

	if (PlayerHUD)
	{
		PlayerHUD->UpdateResources(Gold, Wood);
	}
}

void ATowerPlayerController::BuildATower(TSubclassOf<ATower> TowerClass)
{
	if (bPlayerIsBuilding)
	{
		ClearBuildingTower();

		FActorSpawnParameters FASP;
		FHitResult Hit;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, Hit);
		if (Hit.bBlockingHit)
		{
			FVector MouseAt = Hit.Location;
			TowerToBuild = GetWorld()->SpawnActor<ATower>(TowerClass, MouseAt, FRotator::ZeroRotator, FASP);		
		}
		else
		{
			TowerToBuild = GetWorld()->SpawnActor<ATower>(TowerClass, FVector::ZeroVector, FRotator::ZeroRotator, FASP);
		}
		TowerToBuild->SetTowerMode(ETowerMode::Placing);
	}
}

void ATowerPlayerController::ClearBuildingTower()
{
	if (TowerToBuild)
	{
		TowerToBuild->Destroy();
		TowerToBuild = nullptr;
	}
}

void ATowerPlayerController::UpdateLives(int32 Amount)
{
	Lives = FMath::Clamp(Lives + Amount, 0, 100);
	if (PlayerHUD)
	{
		PlayerHUD->UpdateLivesAmount(Lives);
	}

}
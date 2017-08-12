// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TowerData.h"
#include "TowerPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API ATowerPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ATowerPlayerController();
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	void LeftMousePressed();
	void RightMousePressed();
	void HorizontalMovement(float Amount);
	void VerticalMovement(float Amount);
	void ZoomCamera(float Amount);
	void ToggleBuild();
	void CheckForActions();

	

	// Player is going to move at different speed according to the zoom level.
	void CalculateZoomMovMultiplier();
	void CheckCameraScroll();

	

	/* Those are the HUD related functions cause we dont want the hud
	   to be updating every fucking frame
	*/
	void GainResources(int32 PlusGold, int32 PlusWood);

public:
	UFUNCTION(BlueprintCallable, Category = ThePlayer)
		void BuildATower(TSubclassOf<class ATower> TowerClass);
	UFUNCTION(BlueprintCallable, Category = ThePlayer)
		void ToggleMainMenu();
	UFUNCTION(BlueprintCallable, Category = ThePlayer)
		void UpdateLives(int32 Amount);


private:
	class ATowerPawn* ThePawn;
	void ClearBuildingTower();
	FVector SnapCoordinates(FVector InitialCoords);

public:
	// The speed assigned to that zoom level.
	UPROPERTY(Category = Information, BlueprintReadWrite, EditAnywhere)
		float ZoomMultiplier;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		AActor* SelectedUnit;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		ESelectedUnitType SelectedType;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		int32 Gold;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		int32 Wood;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		int32 Lives;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		uint32 bPlayerIsBuilding : 1;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		uint32 bValidSurface : 1;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		uint32 bShowingMainMenu : 1;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		class ATower* TowerToBuild;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		TSubclassOf<class UUserWidget> PlayerMenuClasss;
	UPROPERTY(Category = Information, BlueprintReadWrite, VisibleAnywhere)
		class UUserWidget* PlayerMenu;
public:
	TSubclassOf<class UUserHUD> PlayerHUDClass;
	class UUserHUD* PlayerHUD;
};

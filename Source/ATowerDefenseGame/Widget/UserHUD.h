// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserHUD.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API UUserHUD : public UUserWidget
{
	GENERATED_BODY()
public:
	UUserHUD(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void UpdateResources(int32 Gold, int32 Wood);
	
	UFUNCTION(BlueprintCallable, Category = "HUD functions")
		void SetupDisplayMode(EDisplayMode DisplayMode);

	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void UpdateWaveHandler(uint8  Index);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void UpdateMinionAmount(uint8 Alive, uint8 Spawned);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void UpdateLivesAmount(int32 Lives);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void ToggleBuildMode(bool ShowTowers);
	UFUNCTION(BlueprintImplementableEvent, Category = "HUD functions")
		void UpdateSelectedActor(AActor* SelectedActor, ESelectedUnitType UnitType);


public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD properties")
		class UGlobalEventHandler* EventHandler;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD properties")
		EDisplayMode HUDDisplayMode;
};

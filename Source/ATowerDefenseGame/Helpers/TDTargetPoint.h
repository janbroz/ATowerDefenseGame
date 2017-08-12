// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "TDTargetPoint.generated.h"

/**
 * 
 */
UCLASS()
class ATOWERDEFENSEGAME_API ATDTargetPoint : public ATargetPoint
{
	GENERATED_BODY()
public:
	ATDTargetPoint();

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 RouteIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		uint32 bIsDestiny : 1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ATDTargetPoint* NextTargetPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector TeleportLocation;

public:
	UFUNCTION()
		int32 GetNextIndex();
};

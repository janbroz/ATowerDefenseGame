// Fill out your copyright notice in the Description page of Project Settings.

#include "ATowerDefenseGame.h"
#include "TDTargetPoint.h"
#include "Minion/TowerMinion.h"
#include "Minion/MinionController.h"
#include "BehaviorTree/BlackboardComponent.h"

ATDTargetPoint::ATDTargetPoint()
{
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	CollisionBox->SetBoxExtent(FVector(128.f, 128.f, 128.f));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATDTargetPoint::OnBoxBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATDTargetPoint::OnBoxEndOverlap);

}


int32 ATDTargetPoint::GetNextIndex()
{
	if (NextTargetPoint)
	{
		if (RouteIndex < NextTargetPoint->RouteIndex)
		{
			return NextTargetPoint->RouteIndex;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

void ATDTargetPoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATowerMinion* Minion = Cast<ATowerMinion>(OtherActor);
	if (Minion)
	{
		// this means point is not the last destination
		AMinionController* MinionController = Cast<AMinionController>(Minion->GetController());
		if (MinionController && MinionController->GetMinionBlackboardComponent())
		{
			MinionController->GetMinionBlackboardComponent()->SetValueAsObject(TEXT("TargetActor"), NextTargetPoint);
			MinionController->GetMinionBlackboardComponent()->SetValueAsInt(TEXT("RouteIndex"), GetNextIndex());

			/*if (RouteIndex >= NextTargetPoint->RouteIndex)
			{
				Minion->SetActorLocation(TeleportLocation);
				MinionController->StopMovement();
			}*/

			// Enemy reached the last route point
			if (bIsDestiny)
			{
				// We dont teleport the minion, but we hit the player!
				//Minion->SetActorLocation(TeleportLocation);
				//MinionController->StopMovement();
				Minion->FinishedObjective();

			}

		}		
	}
}

void ATDTargetPoint::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TArray<AActor*> OverlappingMinions;
	CollisionBox->GetOverlappingActors(OverlappingMinions, TSubclassOf<ATowerMinion>());

	if (NextTargetPoint == nullptr)
	{
		for (auto& Minion : OverlappingMinions)
		{
			Minion->SetActorLocation(TeleportLocation);
			
		}
	}
}
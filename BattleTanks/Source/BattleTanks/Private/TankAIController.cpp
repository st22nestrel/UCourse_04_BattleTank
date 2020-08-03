// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank) {
		auto AITank = Cast<ATank>(GetPawn());
		if (!AITank) {
			UE_LOG(LogTemp, Warning, TEXT("AIPlayerController not possesing a tank"));
			return;
		}
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // leave others as defaults for now

		// Aim towards the player
		AITank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		AITank->Fire();
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController could not find the player"));
};
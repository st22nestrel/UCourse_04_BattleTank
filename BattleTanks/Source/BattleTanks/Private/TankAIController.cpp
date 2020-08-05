// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
}


void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (ensure(PlayerTank)) {
		auto AITank = GetPawn();
		if (!ensure(AITank)) {
			return;
		}
		// Move towards the player
		MoveToActor(PlayerTank, AcceptanceRadius); // leave others as defaults for now

		// Aim towards the player
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		AimingComponent->Fire();
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController could not find the player"));
};
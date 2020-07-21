// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) //protecting us in case no tank is assigned to player
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI possesed tank: %s"), *(ControlledTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

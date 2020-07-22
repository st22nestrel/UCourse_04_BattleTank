// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (!ControlledTank) //protecting us in case no tank is assigned to player
	{
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController not possesing a tank"));
	}
	else if(!PlayerTank){
		UE_LOG(LogTemp, Warning, TEXT("AIPlayerController could not find the player"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI possesed tank: %s, aiming for %s"), *(ControlledTank->GetName()), *(PlayerTank->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) return nullptr;
	return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GetPlayerTank()) {
		auto AITank = GetControlledTank(); // to remove 

		FVector AIHitLocation;
		AITank->AimAt(AIHitLocation);
	}
};
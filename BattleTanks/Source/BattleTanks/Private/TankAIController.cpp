// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto *AIplayer = GetPawn();

	if (!AIplayer) {
		UE_LOG(LogTemp, Warning, TEXT("AI did not found corresponding tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI posseses %s"), *(AIplayer->GetName()));
	}
}

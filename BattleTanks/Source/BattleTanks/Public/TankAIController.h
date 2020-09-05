// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
class UTankAimingComponent;

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	// How close can the AI tank get
	UPROPERTY(EditAnywhere, Category = "Setup", meta = (ClampMin = "1000.0", UIMin = "1000.0", ClampMax = "10000.0", UIMax = "10000.0"))
	float AcceptanceRadius = 8000; //cm?

	UTankAimingComponent* AimingComponent = nullptr;

	virtual void SetPawn(APawn* InPawn) override;

	UFUNCTION()
	void OnPossedTankDeath();
};

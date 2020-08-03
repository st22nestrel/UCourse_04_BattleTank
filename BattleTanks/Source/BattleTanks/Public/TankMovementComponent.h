// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;
/**
 * Responsible for driving the track
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	// Category in string " " prevents weird bugs
	UFUNCTION(BluePrintCallable, Category = "Setup")
	void Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet);

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendMoveBackward(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendMoveReverseRight(float Throw);

	UFUNCTION(BlueprintCallable)
	void IntendMoveReverseLeft(float Throw);

private:
	// Called from the pathfinding logic by the AI controllers
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack* LTrack = nullptr;
	UTankTrack* RTrack = nullptr;

};

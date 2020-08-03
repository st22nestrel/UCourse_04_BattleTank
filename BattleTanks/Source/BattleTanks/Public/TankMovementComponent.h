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
	UFUNCTION(BluePrintCallable, Category = Setup)
	void Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet);

	UFUNCTION(BlueprintCallable)
	void IntendMoveForward(float Throw);

private:
	UTankTrack* LTrack = nullptr;
	UTankTrack* RTrack = nullptr;

};

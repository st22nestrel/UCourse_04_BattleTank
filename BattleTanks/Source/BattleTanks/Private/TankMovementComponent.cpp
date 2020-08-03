// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet) {

	if (!LTrackToSet || !RTrackToSet) return;
	LTrack = LTrackToSet;
	RTrack = RTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);

	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to dual control use //gamepad!
}

void UTankMovementComponent::IntendMoveBackward(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);

	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to dual control use //gamepad!
}

void UTankMovementComponent::IntendMoveReverseRight(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);
	Throw = Throw * 2;

	LTrack->SetThrottle(Throw);
	RTrack->SetThrottle(-Throw);
	// TODO prevent double-speed due to dual control use //gamepad!
}

void UTankMovementComponent::IntendMoveReverseLeft(float Throw) {
	//UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw);
	Throw = Throw * 2;

	LTrack->SetThrottle(-Throw);
	RTrack->SetThrottle(Throw);
	// TODO prevent double-speed due to dual control use //gamepad!
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LTrackToSet, UTankTrack* RTrackToSet) {

	if (!ensure(LTrackToSet && RTrackToSet)) return;
	LTrack = LTrackToSet;
	RTrack = RTrackToSet;
}

// I assume that this function is called with MoveToActor() in TankAIController.cpp
void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	
	// No need to call Super as we're replacing the functionality
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntetion = MoveVelocity.GetSafeNormal();

	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);
	IntendMoveForward( FVector::DotProduct(TankForward, AIForwardIntetion) );
	
	FVector MoveAndRotate = FVector::CrossProduct(TankForward, AIForwardIntetion);
	IntendMoveReverseRight(MoveAndRotate.Z);

};

//////////////////////
// Intend move methods
//////////////////////

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
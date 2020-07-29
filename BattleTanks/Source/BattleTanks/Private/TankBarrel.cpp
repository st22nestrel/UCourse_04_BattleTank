// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "UObject/ConstructorHelpers.h"

UTankBarrel::UTankBarrel()
{

}

void UTankBarrel::Elevate(float RelativeSpeed) {
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);

	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond /* °/s */ * GetWorld()->DeltaTimeSeconds; // FrameIndependent - zisti asi +- kolko herneho casu ubehlo tento frame a tu hodnotu nam vypluje
	auto RawNewRotation = GetRelativeRotation().Pitch + ElevationChange;
	auto PitchRestrict = FMath::Clamp<float>(RawNewRotation, MinElavation, MaxElevation); // static method, does not change any value
																						  // <float> just implicitly says that we are accepting only float values

	SetRelativeRotation(FRotator(PitchRestrict, 0, 0));

	UE_LOG(LogTemp, Warning, TEXT("Barrel->Elevate() called at speed %f"), RelativeSpeed);
}
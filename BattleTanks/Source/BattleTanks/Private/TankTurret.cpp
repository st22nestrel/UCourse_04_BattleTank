// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed) {
	// Move the barrel the right amount this frame
	// Given a max elevation speed, and the frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -2, 2);

	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond /* °/s */ * GetWorld()->DeltaTimeSeconds; // FrameIndependent - zisti asi +- kolko herneho casu ubehlo tento frame a tu hodnotu nam vypluje
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
	//UE_LOG(LogTemp, Warning, TEXT("Turret->Rotate() called at speed %f"), RelativeSpeed);
}
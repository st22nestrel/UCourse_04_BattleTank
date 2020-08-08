// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay(){
	Super::BeginPlay();

	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play") );
	}
}

void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
	//UE_LOG(LogTemp, Warning, TEXT("Ticking"));
}

// TODO maybe find a way to asign this just via blueprint
void ATankPlayerController::AimLock() {
	bAimLocked = !bAimLocked;
}

void ATankPlayerController::AimTowardsCrosshair() {
	if ( !ensure(GetPawn()) ) return; // e.g. if not possessing -> prevents PlayerController_BP crash
	
	if (!bAimLocked) {
		FVector HitLocation; // Out parameter
		if (GetSightRayHitLocation(HitLocation)) {// Has "side-effect", is going to line trace

			AimingComponent->AimAt(HitLocation);

			// TODO Tell controlled tank to aim at this point
		}
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const {

	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) {
		// Line-trace along that look direction, and see what we hit (up to max range)
		if(GetLookVectorHitLocation(LookDirection, OutHitLocation)) return true;
	}
	return true; // just always returns -> assigns given value to FVector& OutHitLocation
				 // for our convenience
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
	FVector CameraWorldLocation; // To be discarted
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		CameraWorldLocation, 
		LookDirection
	);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const {
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility
	)) {
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false; // Line trace didn't succed
}
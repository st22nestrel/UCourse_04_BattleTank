// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false; 

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
	if (!BarrelToSet) return;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
	if (!TurretToSet) return;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) return; //nullptr protection

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHasAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed, // next 3 values sadly must be there to prevent bug
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	//Calculate the OutLaunchVelocity
	if (bHasAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //FVector
	
		auto Time = GetWorld()->GetTimeSeconds();
		//UE_LOG(LogTemp, Warning, TEXT("%f: aim solve found"), Time)
		MoveBarrelTowards(AimDirection);
		
	}
	// I want to rotate turret no matter if I am to able to hit
	// thing I am aiming at -- not working, bHasAimSolution always returns true
	else {
		/*UE_LOG(LogTemp, Warning, TEXT("%s: Boool"), *OutLaunchVelocity.ToString());
		auto AimDirection = OutLaunchVelocity.GetSafeNormal(); //FVector
		UE_LOG(LogTemp, Warning, TEXT("%s: aim solve not found"), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);*/
	}
	
	//if no solution found do nothing
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	// Reverse yaw when rotating turret backwards
	if (DeltaRotator.Yaw < -180 || DeltaRotator.Yaw > 180) {
		DeltaRotator.Yaw = -DeltaRotator.Yaw;
		//UE_LOG(LogTemp, Warning, TEXT("Ci Pana"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("DeltaYaw: %f, AimDirectionYaw: %f, TurretYaw: "), DeltaRotator.Yaw, AimAsRotator.Yaw);

	Barrel->Elevate(DeltaRotator.Pitch);
	if (!Turret) return;
	Turret->Rotate(DeltaRotator.Yaw);
}



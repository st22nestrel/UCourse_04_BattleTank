// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; 

	///////////////////////////////////////////////////////////////////////////
	//static ConstructorHelpers::FObjectFinder<AProjectile>Projectile_BP(TEXT("/Game/Blueprints/Projectile_BP"));
	//rojectileBlueprint = *Projectile_BP.Object;

	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// So that first fire is after initial reload..
	LastFireTime = GetWorld()->GetTimeSeconds();	
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) 
{
	if (!RoundsLeft) {
		FiringStatus = EFiringStatus::OutOfAmmo;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTime) {
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		FiringStatus = EFiringStatus::Aiming;
	}
	else {
		FiringStatus = EFiringStatus::Locked;
	}

}

bool UTankAimingComponent::IsBarrelMoving() {
	if (ThisAimDirection.Equals(Barrel->GetForwardVector(), 0.01)) {
		return false;
	}
	else
		return true;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
		if (!ensure(Barrel)) return; //nullptr protection
		//UE_LOG(LogTemp, Warning, TEXT("I'm HERE!"))


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
			//UE_LOG(LogTemp, Warning, TEXT("Bool value is: %d"), bHasAimSolution ? 1 : 0);
			if (bHasAimSolution)
			{
				ThisAimDirection = OutLaunchVelocity.GetSafeNormal(); //FVector

				auto Time = GetWorld()->GetTimeSeconds();
				//UE_LOG(LogTemp, Warning, TEXT("%f: aim solve found"), Time)
				MoveBarrelTowards(ThisAimDirection);

			}

			/// TODO this + fix aim flickering
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
	if (!ensure(Barrel && Turret)) return;

	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = ThisAimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	// Reverse yaw when rotating turret backwards
	if (DeltaRotator.Yaw < -180 || DeltaRotator.Yaw > 180) {
		DeltaRotator.Yaw = -DeltaRotator.Yaw;
		//UE_LOG(LogTemp, Warning, TEXT("Ci Pana"));
	}
	//UE_LOG(LogTemp, Warning, TEXT("DeltaYaw: %f, AimDirectionYaw: %f, TurretYaw: "), DeltaRotator.Yaw, AimAsRotator.Yaw);

	Turret->Rotate(DeltaRotator.Yaw);
	Barrel->Elevate(DeltaRotator.Pitch);
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const
{
	return FiringStatus;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) return;

	if (FiringStatus != EFiringStatus::Reloading && RoundsLeft) {
		if (!ensure(ProjectileBlueprint)) return;

		// Spawn projectile at the socket location
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		UE_LOG(LogTemp, Warning, TEXT("Feuer frei"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}
}

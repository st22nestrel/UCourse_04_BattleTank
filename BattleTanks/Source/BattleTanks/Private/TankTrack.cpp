// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"
#include "Tank.h"
#include "Gravity/Acceleration.h"

// Just switch workaround off by commenting this
#define WORKAROUND

/*
 * W O R K A R O U N D   F O R   V A N I S H I N G   S T A T I C  M E S H
 * Set static mesh within the constructor manually
 */
UTankTrack::UTankTrack()
{
#ifdef WORKAROUND
	// We simply use the Engine Cone Basic Shape
	static ConstructorHelpers::FObjectFinder<UStaticMesh>SM_Track(TEXT("/Game/TankParts/tank_fbx_Track"));
	UStaticMesh* TrackMesh = SM_Track.Object;
	if (TrackMesh != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Set track mesh %s"), *TrackMesh->GetName());
		this->SetStaticMesh(TrackMesh);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Could not set static mesh to component"));
	}
#endif
}

void UTankTrack::SetThrottle(float Throttle) {
	FString Track = GetName();
	//TODO: Apply acceleration over time to a maximum value
    //TODO: Limit speed due to dual control

    if (Throttle == 0.0f)
    {
        return;
    }

    Throttle = FMath::Clamp<float>(Throttle, -1.0f, 1.0f);
    float CurrentForceAdjustment = (2.3f / FMath::Abs(Throttle));
    float TankMass = Cast<ATank>(GetOwner())->GetMass();
    float MassRelation = (TankMass >= 1000) ? (TankMass / 1000) : 1;
    float TrackMaxDrivingForce = (TankMass * GravityAcceleration * MassRelation * CurrentForceAdjustment);
    float ThrottleChange = (Throttle * TrackMaxDrivingForce);

    FVector ForceApplied = (GetForwardVector() * ThrottleChange);
    ForceApplied.X = FMath::Clamp<float>(ForceApplied.X, -TrackMaxDrivingForce / CurrentForceAdjustment, TrackMaxDrivingForce / CurrentForceAdjustment);
    ForceApplied.Y = FMath::Clamp<float>(ForceApplied.Y, -TrackMaxDrivingForce / CurrentForceAdjustment, TrackMaxDrivingForce / CurrentForceAdjustment);
    ForceApplied.Z = FMath::Clamp<float>(ForceApplied.Z, -TrackMaxDrivingForce / CurrentForceAdjustment, TrackMaxDrivingForce / CurrentForceAdjustment);

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, GetComponentLocation());
}
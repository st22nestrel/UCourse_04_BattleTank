// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

// Just switch workaround off by commenting this
#define WORKAROUND

/*
 * W O R K A R O U N D   F O R   V A N I S H I N G   S T A T I C  M E S H
 * Set static mesh within the constructor manually
 */
UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetNotifyRigidBodyCollision(true);

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

void UTankTrack::BeginPlay() {
	Super::BeginPlay();
		
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {

	UE_LOG(LogTemp, Warning, TEXT("I'm hit, I'm hit !"));
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	
	// TODO add: Super::TickComponent(DeltaTime);

	// Calculate the SlippageSpeed
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity()); // x*velocity of track
	// Work-out the required acceleration this fram to correct
	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways force ( F = m a )
	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // two tracks
	//UE_LOG(LogTemp, Warning, TEXT("Correction force: %s"), *CorrectionForce.ToString());
	TankRoot->AddForce(CorrectionForce);
}

// TODO find better track movemnt
void UTankTrack::SetThrottle(float Throttle) {
	FString Track = GetName();
	//float Time = GetWorld()->GetTimeSeconds();
	//UE_LOG(LogTemp, Warning, TEXT("%s throte : %f"), *Track, Throttle);
	
	// TODO clamp actual throttle value so plaeyr can't over-drive
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
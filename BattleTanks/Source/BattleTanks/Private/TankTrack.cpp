// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	FString Track = GetName();
	//float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%s throte : %f"), *Track, Throttle);
	
	// TODO clamp actual throttle value so plaeyr can't over-drive
}
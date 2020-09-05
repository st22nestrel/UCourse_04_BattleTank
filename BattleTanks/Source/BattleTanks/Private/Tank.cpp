// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// it won't work here probably because of still not knowing about value set in BP
	//CurrentHealth = StartingHealth;
}

float ATank::GetHealthPercent() const {
	return CurrentHealth / StartingHealth;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay(); // Needed for BP Begin Play to run!

	CurrentHealth = StartingHealth;

}

// quite don't understand to what is the return value going, it could be a trash value by the fact that we decrease health in this method, or not?
float  ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	/* Ben's way... return type is incorrect.. idk why to do this
	//
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank died"))
	}
	return DamageToApply;*/

	float DamageToApply = DamageAmount; //FMath::Clamp<float>(DamageAmount, 0, CurrentHealth);
	
	if (CurrentHealth <= 0.f) {
		OnDeath.Broadcast();
	}
	else {
		//UE_LOG(LogTemp, Warning, TEXT("Damage Ammount %f, Damage to apply: %f"), DamageAmount, DamageToApply);
		CurrentHealth -= DamageToApply;
		if (CurrentHealth <= 0.f) {
			OnDeath.Broadcast();
		}
		//UE_LOG(LogTemp, Warning, TEXT("Health %f"), CurrentHealth);
	}

	return DamageToApply;
}

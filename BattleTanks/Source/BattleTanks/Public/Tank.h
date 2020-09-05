// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	UFUNCTION(BluePrintPure, Category = "Health")
	float GetHealthPercent() const;

	FDeath OnDeath;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float StartingHealth = 100;

	//UPROPERTY(VisibleAnywhere, Category = "Health")
	float CurrentHealth = 0;
};

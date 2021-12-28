// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleShooter/Actors/Gun.h"
#include "ShooterCharacter.generated.h"

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AShooterCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

protected:
	virtual void BeginPlay() override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Shoot();
	
private:
	UPROPERTY(EditAnywhere)
	float RotationRate = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;
 	
 	UPROPERTY(VisibleAnywhere)
	float Health;
 	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> Gun_BP;

	UPROPERTY()
	AGun* Gun;
};

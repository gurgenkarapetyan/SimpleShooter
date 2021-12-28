// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
	{
		return;
	}

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr)
	{
		return;
	}

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	
	FVector End = Location + Rotation.Vector() * MaxRange;
	FHitResult Hit;
	if (!UKismetSystemLibrary::LineTraceSingle(GetWorld(), Location, End, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel1), true,
										{this, GetOwner()}, EDrawDebugTrace::ForDuration, Hit, true))
	{
		return;
	}
	
	FVector ShotDirection = -Rotation.Vector();
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
	AActor* HitActor = Hit.GetActor();
	if (!HitActor)
	{
		return;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("HELLO WORLD"));
	FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
	HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
}

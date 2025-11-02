// Fill out your copyright notice in the Description page of Project Settings.

#include "FireballAbility.h"

UFireballAbility::UFireballAbility()
{
	Name = TEXT("Fireball");
	Cooldown = 10.0f;			// ??
	BaseDamage = 10.0f;         // ?? must be from damager
	ProjectileSpeed = 1200.f;
	ExplosionRadius = 300.f;	// blueprint?

	// ready by default
	bIsReady = true;
	CooldownTimer = 0.f;

	bIsSplashDamage = true;
	DamageMultiplier = 3.f;
}

bool UFireballAbility::IsReady()
{
	return bIsReady && OwnerEntity != nullptr;     
}
void UFireballAbility::Use()
{
	if (!IsReady())
	{
		return;
	}

	UWorld* World = nullptr;
	if (OwnerEntity)
	{
		AActor* OwnerActor = Cast<AActor>(OwnerEntity);
		if (OwnerActor)
		{
			World = OwnerActor->GetWorld();
		}
	}

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFireballAbility::Use - no World/Owner"));
		return;
	}

	// dmg calculation
	float OutImpactDmg = 3.0f * BaseDamage;
	float OutAoeDmg    = 1.5f * BaseDamage;

	// Random direction (Z = 0)
	const float RandomYaw = FMath::FRandRange(0.0f, 360.0f);
	const FVector Dir = FRotationMatrix(FRotator(0.0f, RandomYaw, 0.0f)).GetUnitAxis(EAxis::X);

	// spawn position + Z delta
	FVector SpawnLocation = FVector::ZeroVector;
	FRotator SpawnRotation = Dir.Rotation();
	AActor* OwnerActor = Cast<AActor>(OwnerEntity);
	if (OwnerActor)
	{
		SpawnLocation = OwnerActor->GetActorLocation() + FVector(0,0,50.f); 
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor;
	SpawnParams.Instigator = OwnerActor ? OwnerActor->GetInstigator() : nullptr;
	
	// cooldown
	bIsReady = false;
	CooldownTimer = Cooldown;
}
void UFireballAbility::Tick(float DeltaTime)
{
	if (!bIsReady)
	{
		CooldownTimer -= DeltaTime;
		if (CooldownTimer <= 0.0f)
		{
			bIsReady = true;
			CooldownTimer = 0.0f;
		}
	}
}
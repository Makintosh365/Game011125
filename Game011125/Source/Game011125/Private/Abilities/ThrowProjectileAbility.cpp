// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/ThrowProjectileAbility.h"
#include "Entities/Entity.h"
#include "Entities/Hero.h"
#include "Kismet/GameplayStatics.h"

UThrowProjectileAbility::UThrowProjectileAbility()
{
	Name = TEXT("Fireball");
}

bool UThrowProjectileAbility::IsReady()
{
	return bIsReady && ownerEntity != nullptr;     
}

void UThrowProjectileAbility::Use()
{
	if (!IsReady())
	{
		return;
	}

	if (!ProjectileClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFireballAbility::Use - no Projectile"));
		return;
	}

	AActor* OwnerActor = nullptr;
	if (ownerEntity)
	{
		OwnerActor = Cast<AActor>(ownerEntity);
	}

	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFireballAbility::Use - no Owner"));
		return;
	}

	UWorld* World = nullptr;
	if (OwnerActor)
	{
		World = OwnerActor->GetWorld();
	}

	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFireballAbility::Use - no World"));
		return;
	}

	// dmg calculation
	float OutImpactDmg = 3.0f * BaseDamage;
	float OutAoeDmg    = 1.5f * BaseDamage;

	const FVector Dir = OwnerActor->GetActorForwardVector();

	// spawn position + Z delta
	FVector SpawnLocation = OwnerActor->GetTransform().GetLocation() + FVector(0,0,50.f);
	FRotator SpawnRotation = Dir.Rotation();
	FVector SpawnScale = FVector(1, 1, 1);
	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, SpawnScale);

	FActorSpawnParameters SpawnParams;
	// SpawnParams.Owner = OwnerActor;
	// SpawnParams.Instigator = OwnerActor ? OwnerActor->GetInstigator() : nullptr;
	if (AActor* Found = UGameplayStatics::GetActorOfClass(GetWorld(), targetClass))
	{
		auto projectile = World->SpawnActor<AProjectile>(ProjectileClass, SpawnTransform, SpawnParams);
		projectile->Initialize(
			damagedClasses,
			BaseDamage,
			Splash,
			PeriodicDamage,
			DamagerDuration,
			DamagerCooldown,
			targetClass,
			ProjectileSpeed);
	}

	Super::Use();
}

void UThrowProjectileAbility::Tick(float DeltaTime)
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
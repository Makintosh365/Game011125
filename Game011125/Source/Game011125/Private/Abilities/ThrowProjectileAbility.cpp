// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/ThrowProjectileAbility.h"
#include "Entities/Entity.h"
#include "Entities/Hero.h"
#include "Kismet/GameplayStatics.h"

UThrowProjectileAbility::UThrowProjectileAbility()
{
	Name = TEXT("Projectile");
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

	AGameObject* OwnerActor = nullptr;
	if (ownerEntity)
	{
		OwnerActor = Cast<AGameObject>(ownerEntity);
	}

	if (!OwnerActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFireballAbility::Use - no Owner"));
		return;
	}

	UWorld* World = OwnerActor->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Warning, TEXT("UFireballAbility::Use - no World"));
		return;
	}

	// dmg calculation
	float OutImpactDmg = DamageMultiplier * OwnerActor->Stats.CurrentDamage;
	// float OutAoeDmg    = 1.5f * OwnerActor->Stats.CurrentDamage;

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
			OutImpactDmg,
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
	Super::Tick(DeltaTime);
}
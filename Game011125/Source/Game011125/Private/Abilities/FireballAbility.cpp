// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/FireballAbility.h"
#include "Entities/Entity.h"

UFireballAbility::UFireballAbility()
{
	Name = TEXT("Fireball");
}

bool UFireballAbility::IsReady()
{
	return bIsReady && ownerEntity != nullptr;     
}

void UFireballAbility::Use()
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

	// Random direction (Z = 0)
	const float RandomYaw = FMath::FRandRange(0.0f, 360.0f);
	const FVector Dir = FRotationMatrix(FRotator(0.0f, RandomYaw, 0.0f)).GetUnitAxis(EAxis::X);

	// spawn position + Z delta
	FVector SpawnLocation = OwnerActor->GetTransform().GetLocation() + FVector(0,0,50.f);
	FRotator SpawnRotation = Dir.Rotation();
	FVector SpawnScale = FVector(1, 1, 1);
	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, SpawnScale);

	FActorSpawnParameters SpawnParams;
	// SpawnParams.Owner = OwnerActor;
	// SpawnParams.Instigator = OwnerActor ? OwnerActor->GetInstigator() : nullptr;
	auto damager = World->SpawnActor<ADamager>(ProjectileClass, SpawnTransform, SpawnParams);
	damager->Initialize(DamagedClasses);
	
	Super::Use();
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
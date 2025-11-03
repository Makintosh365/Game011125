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
	Super::Use();
	
	if (!IsReady())
	{
		return;
	}
	
	UWorld* World = nullptr;
	if (ownerEntity)
	{
		AActor* OwnerActor = Cast<AActor>(ownerEntity);
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
	AActor* OwnerActor = Cast<AActor>(ownerEntity);
	if (OwnerActor)
	{
		SpawnLocation = OwnerActor->GetActorLocation() + FVector(0,0,50.f); 
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor;
	SpawnParams.Instigator = OwnerActor ? OwnerActor->GetInstigator() : nullptr;
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
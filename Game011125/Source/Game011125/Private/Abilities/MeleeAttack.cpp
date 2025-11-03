// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/MeleeAttack.h"

#include "Kismet/GameplayStatics.h"

void UMeleeAttack::Use()
{
	if (!IsReady())
	{
		return;
	}

	if (!DamagerClass)
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

	AGameObject* targetObject = nullptr;
	if (AActor* Found = UGameplayStatics::GetActorOfClass(GetWorld(), targetClass))
		targetObject = Cast<AGameObject>(Found);

	if (!targetObject)
		return;
	
	const FVector MyLocation = OwnerActor->GetActorLocation();
	const FVector TargetLocation = targetObject->GetActorLocation();

	FVector ToTarget = TargetLocation - MyLocation;
	const float DistanceToHero = ToTarget.Size();
	ToTarget.Normalize();

	const FVector SpawnLocation = MyLocation + ToTarget * SpawnDistance;

	FRotator SpawnRotation = ToTarget.Rotation();
	FVector SpawnScale = FVector(1, 1, 1);
	FTransform SpawnTransform = FTransform(SpawnRotation, SpawnLocation, SpawnScale);

	FActorSpawnParameters SpawnParams;
	// SpawnParams.Owner = OwnerActor;
	// SpawnParams.Instigator = OwnerActor ? OwnerActor->GetInstigator() : nullptr;
	if (AActor* Found = UGameplayStatics::GetActorOfClass(GetWorld(), targetClass))
	{
		auto damager = World->SpawnActor<ADamager>(DamagerClass, SpawnTransform, SpawnParams);
		damager->Initialize(
			damagedClasses,
			OutImpactDmg,
			Splash,
			PeriodicDamage,
			DamagerDuration,
			DamagerCooldown);
	}

	Super::Use();
}

bool UMeleeAttack::IsReady()
{
	return Super::IsReady();
}

void UMeleeAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

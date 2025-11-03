// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "Damagers/Projectile.h"
#include "ThrowProjectileAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API UThrowProjectileAbility : public UAbility
{
	GENERATED_BODY()

public:
	UThrowProjectileAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

	//Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float ProjectileSpeed = 1000.f;

	// ExplosionRadius (Aoe)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	bool Explode = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	float ExplosionRadius = 300.f;
	
	void Use() override;
	bool IsReady() override;
	void Tick(float DeltaTime) override;
};

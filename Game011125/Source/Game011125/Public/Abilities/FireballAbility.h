// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Ability.h"
#include "Damagers/Projectile.h"
#include "FireballAbility.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API UFireballAbility : public UAbility
{
	GENERATED_BODY()

public:
	UFireballAbility();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball")
	TSubclassOf<AProjectile> ProjectileClass;

	//BaseDamage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball", meta = (ClampMin = 0.0f))
	float BaseDamage = 0.0f;

	//Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball")
	float ProjectileSpeed = 1200.f;

	// ExplosionRadius (Aoe)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball")
	float ExplosionRadius = 300.f;
	
	void Use() override;
	bool IsReady() override;
	void Tick(float DeltaTime) override;
};

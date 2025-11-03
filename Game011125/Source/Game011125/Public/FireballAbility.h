// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "FireballAbility.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAME011125_API UFireballAbility : public UAbility
{
	GENERATED_BODY()

public:
	UFireballAbility();

	//BaseDamage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball")
	float BaseDamage;

	//Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball")
	float ProjectileSpeed;

	// ExplosionRadius (Aoe)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fireball")
	float ExplosionRadius;
	
	void Use() override;
	bool IsReady() override;
	void Tick(float DeltaTime) override;
};

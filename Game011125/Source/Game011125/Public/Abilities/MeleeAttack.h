// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "Damagers/Damager.h"
#include "MeleeAttack.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API UMeleeAttack : public UAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	TSubclassOf<ADamager> DamagerClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Melee")
	float SpawnDistance = 50.0f;

	void Use() override;
	bool IsReady() override;
	void Tick(float DeltaTime) override;
};

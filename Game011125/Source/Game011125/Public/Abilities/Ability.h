// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"
#include "Interfaces/ICanUseAbilities.h"
#include "Ability.generated.h"

// Forward declaration
class AEntity;

UCLASS(Abstract, Blueprintable) // Abstract
class GAME011125_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UAbility();

	virtual void Initialize(
		AEntity* owner,
		TSubclassOf<AGameObject> FollowedClass,
		const TSet<TSubclassOf<AGameObject>>& DamagedClasses);

	// features

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability", meta = (ClampMin = 0.01f))
	float AbilityCooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damager")
	float DamageMultiplier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Damager")
	bool Splash = false;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Damager")
	bool PeriodicDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Damager", meta = (ClampMin = 0.01f))
	float DamagerDuration = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Ability|Damager", meta = (ClampMin = 0.01f))
	float DamagerCooldown = 5.0f;


	//State

	UPROPERTY(BlueprintReadOnly, Category = "Ability|State")
	bool bIsReady;

	UPROPERTY(BlueprintReadOnly, Category = "Ability|State")
	float CooldownTimer;

	//Methods

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void Use();

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual bool IsReady();

	virtual void SetOwner(ICanUseAbilities* owner);

	//UObject does not have a Tick by default. It should be "ticked" by the owner (Entity)
	virtual void Tick(float DeltaTime);

protected:
	//Ability you need to know who is using it (to spawn a fireball on his behalf)
	ICanUseAbilities* ownerEntity;

	TSet<TSubclassOf<AGameObject>> damagedClasses;
	
	TSubclassOf<AGameObject> targetClass;
};
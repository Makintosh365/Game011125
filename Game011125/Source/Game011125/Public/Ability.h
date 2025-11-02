// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Ability.generated.h"

// Forward declaration
class AEntity;

UCLASS(Abstract, Blueprintable) // Abstract
class GAME011125_API UAbility : public UObject
{
	GENERATED_BODY()

public:
	UAbility();

	// features

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float Cooldown;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	bool bIsSplashDamage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability")
	float DamageMultiplier;

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

	//help functions

	//UObject does not have a Tick by default. It should be "ticked" by the owner (Entity)
	virtual void Tick(float DeltaTime);

	//Ability you need to know who is using it (to spawn a fireball on his behalf)
	UPROPERTY(BlueprintReadOnly, Category = "Ability")
	AEntity* OwnerEntity;
};
// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Entity.h" //OwnerEntity

UAbility::UAbility()
{
	// default value
	Name = "Default Ability";
	Cooldown = 1.0f;
	bIsSplashDamage = false;
	DamageMultiplier = 1.0f;

	bIsReady = true;
	CooldownTimer = 0.0f;
	OwnerEntity = nullptr;
}

//This method will be called from the owner's Ticket (Entity)
void UAbility::Tick(float DeltaTime)
{
	if (!bIsReady)
	{
		CooldownTimer -= DeltaTime;
		if (CooldownTimer <= 0.0f)
		{
			bIsReady = true;
		}
	}
}

//Basic Use implementation: checks readiness and triggers a cooldown
void UAbility::Use()
{
	if (IsReady())
	{
		bIsReady = false;
		CooldownTimer = Cooldown;
		UE_LOG(LogTemp, Warning, TEXT("Base Ability Used. This should be overridden."));
	}
}

//Basic IsReady implementation: just returns a flag
bool UAbility::IsReady()
{
	return bIsReady;
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "Buff.h"
#include "Entity.h"

UBuff::UBuff()
{
	Name = "Default Buff";
	hpBonus = 0.0f;
	speedBonus = 0.0f;
	damageBonus = 0.0f;
	OwnerEntity = nullptr;
}

// base realization Apply
void UBuff::Apply_Implementation(AEntity* TargetEntity)
{
	if (TargetEntity)
	{
		OwnerEntity = TargetEntity;
		UE_LOG(LogTemp, Warning, TEXT("Buff '%s' applied to %s. (Base implementation)"), *Name, *TargetEntity->GetName());

		// include logical
	}
}

// base realization remove
void UBuff::Remove_Implementation()
{
	if (OwnerEntity)
	{
		UE_LOG(LogTemp, Warning, TEXT("Buff '%s' removed from %s. (Base implementation)"), *Name, *OwnerEntity->GetName());

		// include logical

	}
	OwnerEntity = nullptr;
}
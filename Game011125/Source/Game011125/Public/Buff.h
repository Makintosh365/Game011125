// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Buff.generated.h"

class AEntity;


UCLASS(Abstract, Blueprintable, Category = "Buffs")
class GAME011125_API UBuff : public UObject
{
	GENERATED_BODY()

public:
	// constructor
	UBuff();

	//features buffs

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
	float hpBonus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
	float speedBonus;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
	float damageBonus;
};

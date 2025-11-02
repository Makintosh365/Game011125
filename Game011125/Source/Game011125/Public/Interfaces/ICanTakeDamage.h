// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICanTakeDamage.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCanTakeDamage : public UInterface
{
	GENERATED_BODY()
};

class GAME011125_API ICanTakeDamage
{
	GENERATED_BODY()

public:
	virtual void TakeDamage(float damage) { };
};

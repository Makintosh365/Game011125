// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICanUseAbilities.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCanUseAbilities : public UInterface
{
	GENERATED_BODY()
};

class ICanUseAbilities
{
	GENERATED_BODY()

public:
	virtual bool UseCurrentAbility();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICanUseBuffs.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCanUseBuffs : public UInterface
{
	GENERATED_BODY()
};

class GAME011125_API ICanUseBuffs
{
	GENERATED_BODY()

public:
	virtual bool UseBuff() { return false; };
};

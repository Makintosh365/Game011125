// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameObject.h"
#include "UObject/Interface.h"
#include "CoreMinimal.h"
#include "ICanDealDamage.generated.h"


UINTERFACE(MinimalAPI, Blueprintable)
class UCanDealDamage: public UInterface
{
	GENERATED_BODY()
};

class GAME011125_API ICanDealDamage
{
	GENERATED_BODY()

public:
	virtual bool DealDamage(AGameObject* target) { return false; };
};

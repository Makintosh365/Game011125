// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ICanDealDamage.generated.h"

class UGameObject;


UINTERFACE(MinimalAPI, Blueprintable)
class UCanDealDamage: public UInterface
{
	GENERATED_BODY()
};

class ICanDealDamage
{
	GENERATED_BODY()

public:
	virtual void DealDamage(TSharedPtr<UGameObject> damagedObject);
};

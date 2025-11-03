// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Hero.generated.h"

UCLASS(Abstract, Blueprintable)
class GAME011125_API AHero : public AEntity
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHero();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

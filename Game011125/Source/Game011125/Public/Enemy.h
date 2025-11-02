// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Enemy.generated.h"

class AHero;

UCLASS(Abstract, Blueprintable)
class GAME011125_API AEnemy : public AEntity
{
	GENERATED_BODY()

public:

	AEnemy();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AHero* HeroTarget = nullptr;

	UFUNCTION(BlueprintCallable, Category = "References")
	void SetHeroTarget(AHero* NewHero);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float FollowDistance = 150.0f;   

protected:
	virtual void BeginPlay() override;


};

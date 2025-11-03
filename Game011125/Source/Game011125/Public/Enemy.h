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
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Hero pointer
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AHero* HeroTarget;

	UFUNCTION(BlueprintCallable, Category = "References")
	void SetHeroTarget(AHero* NewHero);
};

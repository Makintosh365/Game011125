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
	//--------------------------------------------------------------------------
	// --- Конструктор
	AEnemy();
	//--------------------------------------------------------------------------
	// --- Тик
	virtual void Tick(float DeltaTime) override;

	//--------------------------------------------------------------------------
	// --- Цель (лидер, не игрок)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	AHero* HeroTarget = nullptr;

	//--------------------------------------------------------------------------
	// --- Задать цель из блюпринта/кода
	UFUNCTION(BlueprintCallable, Category = "References")
	void SetHeroTarget(AHero* NewHero);

	//--------------------------------------------------------------------------
	// --- Параметры движения (вот тут самое важное — тут есть FollowDistance!)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float FollowDistance = 150.0f;   // на каком расстоянии останавливаемся

protected:
	//--------------------------------------------------------------------------
	// --- Жизненный цикл
	virtual void BeginPlay() override;


};

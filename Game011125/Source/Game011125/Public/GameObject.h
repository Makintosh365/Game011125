// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stats.h"
#include "GameObject.generated.h"



UCLASS(Abstract)
class GAME011125_API AGameObject : public AActor
{
	GENERATED_BODY()
public:
	AGameObject();

	//--------------------------------------------------------------------------
	// --- Тик
	virtual void Tick(float DeltaTime) override;

	//----------------------------------------------------------------------
	// --- Характеристики
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStats Stats;

	//----------------------------------------------------------------------
	// --- Проверка жив ли объект
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsAlive() const { return Stats.bIsAlive; }


	~AGameObject();
protected:
	//--------------------------------------------------------------------------
	// --- Инициализация при появлении в мире
	virtual void BeginPlay() override;

	//-------------------------------------------------------------------------- 
	// --- Смерть объекта (по умолчанию просто уничтожаем)
	UFUNCTION(BlueprintNativeEvent, Category = "Combat")
	void OnDeath();

	virtual void OnDeath_Implementation();
};

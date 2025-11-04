// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Stats.h"
#include "GameObject.generated.h"


UCLASS(Abstract, Blueprintable)
class GAME011125_API AGameObject : public AActor
{
	GENERATED_BODY()
public:
	AGameObject();

	//--------------------------------------------------------------------------
	// --- Per-frame update
	virtual void Tick(float DeltaTime) override;

	//--------------------------------------------------------------------------
	// --- Character / actor stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	FStats Stats;

	//--------------------------------------------------------------------------
	// --- Check if the object is currently alive
	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool IsAlive() const { return Stats.CurrentHP > 0; }

	~AGameObject();
	
protected:
	//--------------------------------------------------------------------------
	// --- Called when the actor is spawned or the game starts
	virtual void BeginPlay() override;

	//--------------------------------------------------------------------------
	// --- Death handling (by default just destroy the actor)
	virtual void OnDeath();
};

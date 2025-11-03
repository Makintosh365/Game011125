// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damager.h"
#include "Projectile.generated.h"

UCLASS(Abstract, Blueprintable)
class GAME011125_API AProjectile : public ADamager
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
	
	virtual void Initialize(
			const TSet<TSubclassOf<AGameObject>>& DamagedClasses,
			float Damage,
			bool Splash,
			bool PeriodicDamage,
			float Duration,
			float Cooldown,
			TSubclassOf<AGameObject> TargetClass,
			float speed);

	virtual void PostInitProperties() override;

	void SetTargetClass(const TSubclassOf<AGameObject>& TargetClass);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bIsFollowing = false;
	
	UPROPERTY()
	float projectileSpeed = 0.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

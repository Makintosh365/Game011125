// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Interfaces/ICanDealDamage.h"
#include "Interfaces/ICanTakeDamage.h"
#include "Damager.generated.h"

class AGameObject;


/**
 * 
 */
UCLASS(Abstract)
class GAME011125_API ADamager :
	public AActor,	// Replace with AGameObject
	public ICanDealDamage
{
	GENERATED_BODY()

public:
	// ADamager();

	virtual void Tick(float DeltaSeconds) override;

	bool DealDamage(AGameObject* target) override;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default Values")
	// TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values", meta = (ClampMin = 0.0f))
	float Damage = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values")
	bool Splash = false;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values")
	bool PeriodicDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values", meta = (ClampMin = 0.0f))
	float Cooldown = 1.0f;

private:
	float timeCurrent;
	TSet<ICanTakeDamage*> collidingObjects;

	// UFUNCTION()
	// void OnCollisionStartCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
	// 								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	// 								  bool bFromSweep, const FHitResult& SweepResult);
	//
	// UFUNCTION()
	// void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	// 						 UPrimitiveComponent* OtherComp, FVector NormalImpulse, 
	// 						 const FHitResult& Hit);

	bool OnCooldown() const;
	void ResetTimer();
};

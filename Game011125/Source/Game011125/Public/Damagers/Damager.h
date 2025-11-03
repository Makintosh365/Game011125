// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Interfaces/ICanDealDamage.h"
#include "Damager.generated.h"

class AGameObject;


/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API ADamager :
	public AActor,
	public ICanDealDamage
{
	GENERATED_BODY()

public:
	ADamager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;

	bool DealDamage(AGameObject* Target) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default Values")
	TObjectPtr<USphereComponent> CollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values", meta = (ClampMin = 0.0f))
	float Damage = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values")
	bool Splash = false;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values")
	bool PeriodicDamage = false;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values", meta = (ClampMin = 0.01f))
	float Cooldown = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Default Values", meta = (ClampMin = 0.01f))
	float Duration = 5.0f;

private:
	float timeFromLastDamage;
	float timeFromStart;
	bool bDamageStarted = false;
	
	TSet<AGameObject*> damagedObjects;

	UFUNCTION()
	void OnCollisionStartCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
								  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
								  bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCollisionEndCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	bool LifetimeExpired() const;
	bool IsOnCooldown() const;
	void ResetTimer();
};

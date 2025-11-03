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
	virtual void Initialize(
		const TSet<TSubclassOf<AGameObject>>& DamagedClasses,
		float Damage,
		bool Splash,
		bool PeriodicDamage,
		float Duration,
		float Cooldown);
	
	virtual void Tick(float DeltaSeconds) override;

	bool DealDamage(AGameObject* Target) override;

	void SetDamagedClasses(const TSet<TSubclassOf<AGameObject>>& DamagedClasses);

	UPROPERTY(EditAnywhere, Category = "Default Values")
	bool IsMelee = false;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default Values")
	TObjectPtr<USphereComponent> CollisionComponent;

protected:
	float damage = 0.0f;
	bool splash = false;
	bool periodicDamage = false;
	float duration = 5.0f;
	float cooldown = 1.0f;
	
	float timeFromLastDamage;
	float timeFromStart;
	bool bDamageStarted = false;

	// Target (followed)
	TSubclassOf<AGameObject> targetClass;

	UPROPERTY()
	AGameObject* targetObject;
	
	// Damaged
	TSet<TSubclassOf<AGameObject>> damagedClasses;
	
	UPROPERTY()
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

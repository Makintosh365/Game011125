// Fill out your copyright notice in the Description page of Project Settings.

#include "Damager.h"

#include "GameObject.h"
#include "Components/SphereComponent.h"
//
//
// ADamager::ADamager()
// {
// 	PrimaryActorTick.bCanEverTick = true;
// 	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
// 	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamager::OnCollisionStartCallback);
// 	CollisionComponent->OnComponentHit.AddDynamic(this, &ADamager::OnHit);
// }

void ADamager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	timeCurrent += DeltaSeconds;
}

bool ADamager::DealDamage(AGameObject* target)
{
	ICanDealDamage::DealDamage(target);

	if (ICanTakeDamage* damagedObject = Cast<ICanTakeDamage>(target))
	{
		if (Splash)
		{
			if (PeriodicDamage)
			{
				if (collidingObjects.Contains(damagedObject))
				{
					collidingObjects.Reset();
					ResetTimer();
				}
				else
				{
					damagedObject->TakeDamage(Damage);
					collidingObjects.Add(damagedObject);
				}
			}
			else
			{
				if (collidingObjects.Contains(damagedObject))
				{
					Destroy();
					return true;
				}
				else
				{
					damagedObject->TakeDamage(Damage);
					collidingObjects.Add(damagedObject);
				}
			}
		}
		else
		{
			damagedObject->TakeDamage(Damage);
			Destroy();
			return true;
		}
	}
	return false;
}

// void ADamager::OnCollisionStartCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
// 									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
// 									  bool bFromSweep, const FHitResult& SweepResult)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Damager collision callback");
// 	if (AGameObject* target = Cast<AGameObject>(OtherActor))
// 		DealDamage(target);
// }
//
// void ADamager::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
// 	FVector NormalImpulse, const FHitResult& Hit)
// {
// 	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Damager hit callback");
// }

bool ADamager::OnCooldown() const
{
	return timeCurrent < Cooldown;
}

void ADamager::ResetTimer()
{
	timeCurrent = 0.0f;
}

// Fill out your copyright notice in the Description page of Project Settings.

#include "Damagers/Damager.h"

#include "GameObject.h"
#include "Components/SphereComponent.h"
#include "Interfaces/ICanTakeDamage.h"


ADamager::ADamager()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionComponent;
}

void ADamager::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamager::OnCollisionStartCallback);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ADamager::OnCollisionEndCallback);
}

void ADamager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bDamageStarted)
		return;
	
	if (!PeriodicDamage)
	{
		for (AGameObject* target : damagedObjects)
			DealDamage(target);
		Destroy();
		return;
	}
	else
	{
		if (LifetimeExpired())
		{
			Destroy();
			return;
		}

		if (!IsOnCooldown())
		{
			for (AGameObject* target : damagedObjects)
				DealDamage(target);

			ResetTimer();
		}
	}

	timeFromLastDamage += DeltaSeconds;
	timeFromStart += DeltaSeconds;
}

bool ADamager::DealDamage(AGameObject* Target)
{
	ICanDealDamage::DealDamage(Target);
	
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Damager deal damage");
	
	if (ICanTakeDamage* damageable = Cast<ICanTakeDamage>(Target))
	{
		damageable->TakeDamage(Damage);
		return true;
	}
	return false;
}

void ADamager::OnCollisionStartCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
									  bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Damager collision start");
	if (AGameObject* target = Cast<AGameObject>(OtherActor))
	{
		if (!Splash)
		{
			DealDamage(target);
			Destroy();
		}
		else
		{
			damagedObjects.Add(target);
			bDamageStarted = true;
		}
	}
}

void ADamager::OnCollisionEndCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
									UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Damager collision end");
	damagedObjects.Remove(Cast<AGameObject>(OtherActor));
}

bool ADamager::LifetimeExpired() const
{
	return timeFromStart >= Duration;
}

bool ADamager::IsOnCooldown() const
{
	return timeFromLastDamage < Cooldown;
}

void ADamager::ResetTimer()
{
	timeFromLastDamage = 0.0f;
}

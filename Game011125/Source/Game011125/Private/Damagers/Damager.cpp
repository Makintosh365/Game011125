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
	
	CollisionComponent->SetGenerateOverlapEvents(true);
	CollisionComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamager::OnCollisionStartCallback);
	CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ADamager::OnCollisionEndCallback);
}

void ADamager::Initialize(const TSet<TSubclassOf<AGameObject>>& DamagedClasses, float Damage, bool Splash,
	bool PeriodicDamage, float Duration, float Cooldown)
{
	SetDamagedClasses(DamagedClasses);
	damage = Damage;
	splash = Splash;
	periodicDamage = PeriodicDamage;
	duration = Duration;
	cooldown = Cooldown;
}

void ADamager::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsMelee)
	{
		TArray<AActor*> OverlappingActors;
		CollisionComponent->GetOverlappingActors(OverlappingActors);
		for (auto overlappingActor : OverlappingActors)
		{
			if (auto target = Cast<AGameObject>(overlappingActor))
			{
				for (TSubclassOf<AGameObject> damageableClass : damagedClasses)
				{
					if (target->GetClass()->IsChildOf(damageableClass))
						DealDamage(target);
				}
			}
		}
		Destroy();
	}
	
	if (!bDamageStarted)
		return;
	
	if (!periodicDamage)
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
		damageable->TakeDamage(damage);
		return true;
	}
	return false;
}

void ADamager::SetDamagedClasses(const TSet<TSubclassOf<AGameObject>>& DamagedClasses)
{
	damagedClasses = DamagedClasses;
}

void ADamager::OnCollisionStartCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                                        bool bFromSweep, const FHitResult& SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "Damager collision start");
	if (AGameObject* target = Cast<AGameObject>(OtherActor))
	{
		bool damageAllowed = false;
		for (TSubclassOf<AGameObject> damageableClass : damagedClasses)
		{
			if (target->GetClass()->IsChildOf(damageableClass))
			{
				damageAllowed = true;
			}
		}
		if (!damageAllowed)
			return;

		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Damager collision start");
		if (!splash)
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
	if (damagedObjects.Remove(Cast<AGameObject>(OtherActor)))
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Damager collision end");
}

bool ADamager::LifetimeExpired() const
{
	return timeFromStart >= duration;
}

bool ADamager::IsOnCooldown() const
{
	return timeFromLastDamage < cooldown;
}

void ADamager::ResetTimer()
{
	timeFromLastDamage = 0.0f;
}

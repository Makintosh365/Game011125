// Fill out your copyright notice in the Description page of Project Settings.


#include "Damagers/Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::Initialize(const TSet<TSubclassOf<AGameObject>>& DamagedClasses, float Damage, bool Splash,
	bool PeriodicDamage,float Duration, float Cooldown, TSubclassOf<AGameObject> TargetClass, float speed)
{
	Super::Initialize(DamagedClasses, Damage, Splash, PeriodicDamage, Duration, Cooldown);

	targetClass = TargetClass;
	projectileSpeed = speed;
}

void AProjectile::PostInitProperties()
{
	Super::PostInitProperties();

}

void AProjectile::SetTargetClass(const TSubclassOf<AGameObject>& TargetClass)
{
	targetClass = TargetClass;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	if (targetObject && !targetObject->IsAlive())
	{
		Destroy();
		return;
	}

	if (!targetObject && targetClass)
	{
		if (AActor* Found = UGameplayStatics::GetActorOfClass(GetWorld(), targetClass))
		{
			targetObject = Cast<AGameObject>(Found);
			bIsFollowing = true;
		}
	}

	const FVector MyLocation = GetActorLocation();
	const FVector TargetLocation = targetObject->GetActorLocation();

	FVector ToTarget = TargetLocation - MyLocation;
	const float DistanceToHero = ToTarget.Size();

	ToTarget.Normalize();
	const FVector DeltaMove = ToTarget * projectileSpeed * DeltaTime;

	// AddActorWorldOffset with sweep = true so we don't walk through walls
	AddActorWorldOffset(DeltaMove, true);
	
	FRotator FacingRotator = ToTarget.Rotation();
	SetActorRotation(FacingRotator, ETeleportType::None);
	
	Super::Tick(DeltaTime);
}

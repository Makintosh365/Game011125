// Enemy.cpp
// -----------------------------------------------------------------------------

#include "Entities/Enemy.h"
#include "Entities/Hero.h"
#include "Kismet/GameplayStatics.h"
#include "Stats.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	Stats = MakeEnemyDefaultStats();
}

//------------------------------------------------------------------------------
// --- BeginPlay
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (HeroTarget == nullptr)
	{
		AHero* GlobalHero = AHero::GetCurrentHero();
		if (GlobalHero)
		{
			HeroTarget = GlobalHero;
		}
		else
		{
			AActor* Found = UGameplayStatics::GetActorOfClass(GetWorld(), AHero::StaticClass());
			if (Found)
			{
				HeroTarget = Cast<AHero>(Found);
			}
		}
	}

}

//------------------------------------------------------------------------------
// --- Tick
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!HeroTarget || !IsValid(HeroTarget))
	{
		return;
	}

	const FVector MyLocation = GetActorLocation();
	const FVector HeroLocation = HeroTarget->GetActorLocation();

	FVector ToHero = HeroLocation - MyLocation;
	const float DistanceToHero = ToHero.Size();

	//  DIE
	if (DistanceToHero >= FollowDistance)
	{
		OnDeath();
	}

	ToHero.Normalize();
	const FVector DeltaMove = ToHero * Stats.CurrentSpeed * DeltaTime;

	if (FollowHero)
	{
		// AddActorWorldOffset with sweep = true so we don't walk through walls
		AddActorWorldOffset(DeltaMove, true);
	}
}

void AEnemy::SetHeroTarget(AHero* NewHero)
{
	HeroTarget = NewHero;
}

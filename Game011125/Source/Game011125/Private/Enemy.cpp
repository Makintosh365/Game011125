// Enemy.cpp
// -----------------------------------------------------------------------------

#include "Enemy.h"
#include "Hero.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
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

	// Если цели нет или она уже уничтожена — ничего не делаем
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

	// AddActorWorldOffset with sweep = true so we don't walk through walls
	AddActorWorldOffset(DeltaMove, true);
}

void AEnemy::SetHeroTarget(AHero* NewHero)
{
	HeroTarget = NewHero;
}

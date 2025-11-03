// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Hero.h"  
#include "Kismet/GameplayStatics.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (HeroTarget == nullptr)
	{
		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		if (PlayerPawn)
		{
			AHero* FoundHero = Cast<AHero>(PlayerPawn);
			if (FoundHero)
			{
				HeroTarget = FoundHero;
			}
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::SetHeroTarget(AHero* NewHero)
{
	HeroTarget = NewHero;
}


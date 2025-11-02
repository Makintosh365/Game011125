// Fill out your copyright notice in the Description page of Project Settings.


// Hero.cpp
// -----------------------------------------------------------------------------

#include "Hero.h"

AHero* AHero::CurrentHero = nullptr;

AHero::AHero()
{

	PrimaryActorTick.bCanEverTick = true;
}

void AHero::BeginPlay()
{
	Super::BeginPlay();

	CurrentHero = this;
}

void AHero::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentHero == this)
	{
		CurrentHero = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}





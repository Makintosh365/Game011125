// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UnheroGameModeBase.h"


void AUnheroGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	levelStartupWidget = CreateWidget<UUserWidget>(GetWorld(), LevelStartupWidgetClass);
	if (levelStartupWidget)
		levelStartupWidget->AddToViewport();
}

void AUnheroGameModeBase::PostInitProperties()
{
	Super::PostInitProperties();
}

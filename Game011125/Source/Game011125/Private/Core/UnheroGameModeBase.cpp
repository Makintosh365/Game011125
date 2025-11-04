// Fill out your copyright notice in the Description page of Project Settings.

#include "Core/UnheroGameModeBase.h"
#include "Core/UnheroGameInstance.h"
#include "Core/UnheroPlayerController.h"


void AUnheroGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	if (auto world = GetWorld())
	{
		if (auto gameInstance = Cast<UUnheroGameInstance>(world->GetGameInstance()))
		{
			if (gameInstance->LoadUI)
			{
				levelStartupWidget = CreateWidget<UUserWidget>(GetWorld(), LevelStartupWidgetClass);
				if (levelStartupWidget)
					levelStartupWidget->AddToViewport();
			}
		}
	}
}

AUnheroGameModeBase::AUnheroGameModeBase()
{
	PlayerControllerClass = AUnheroPlayerController::StaticClass();
}

void AUnheroGameModeBase::PostInitProperties()
{
	Super::PostInitProperties();
}

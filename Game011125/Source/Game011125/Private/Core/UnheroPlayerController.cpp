// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UnheroPlayerController.h"

void AUnheroPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeUIOnly inputMode;
	inputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	bShowMouseCursor = true;
	SetInputMode(inputMode);
}

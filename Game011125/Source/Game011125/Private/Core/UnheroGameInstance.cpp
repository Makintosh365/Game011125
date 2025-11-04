// Fill out your copyright notice in the Description page of Project Settings.


#include "Core/UnheroGameInstance.h"

#include "Kismet/GameplayStatics.h"

void UUnheroGameInstance::Init()
{
	Super::Init();

	UGameplayStatics::OpenLevel(GetWorld(), DefaultLevelName);
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "UnheroGameModeBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API AUnheroGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Widget")
	TSubclassOf<UUserWidget> LevelStartupWidgetClass;
	
	virtual void PostInitProperties() override;

private:
	UPROPERTY()
	UUserWidget* levelStartupWidget = nullptr;	
};

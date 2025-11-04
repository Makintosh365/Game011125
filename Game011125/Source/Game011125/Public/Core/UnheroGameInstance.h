// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UnheroGameInstance.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API UUnheroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	FName DefaultLevelName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	bool StartWithDefaultLevel = true;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	bool LoadUI = true;
	
	virtual void Init() override;
};

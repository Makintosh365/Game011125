// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UnheroGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAME011125_API UUnheroGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Level")
	FName DefaultLevelName;
	
	virtual void Init() override;
};

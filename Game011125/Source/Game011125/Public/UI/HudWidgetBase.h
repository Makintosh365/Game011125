// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HudWidgetBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class GAME011125_API UHudWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBarHP;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBarXP;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TimerText;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageGoblin;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageVampire;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UImage* ImageDragon;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonGoblin;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonVampire;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonDragon;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* GoblinText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* VampireText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* DragonText;

private:
	UFUNCTION()
	void OnGoblinClicked();

	UFUNCTION()
	void OnVampireClicked();

	UFUNCTION()
	void OnDragonClicked();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "HudWidgetBase.generated.h"

class AHero;   

class AEnemySpawnManager;
UCLASS(Abstract, Blueprintable)
class GAME011125_API UHudWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:

    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
    FText GoblinReadyText = FText::FromString("Goblin");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
    FText VampireReadyText = FText::FromString("Vampire");

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
    FText DragonReadyText = FText::FromString("Dragon");

	virtual void NativeConstruct() override;

    // === HP ===
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD|HP")
    bool bSmoothHP = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="HUD|HP", meta=(ClampMin="0.0"))
    float HPSmoothSpeed = 5.0f; // чем больше — тем быстрее догоняет


	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBarHP;
		
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
	UPROPERTY() AEnemySpawnManager* SpawnManager = nullptr;
    UPROPERTY() AHero* HeroRef = nullptr;  
	
	UFUNCTION()
	void OnGoblinClicked();

	UFUNCTION()
	void OnVampireClicked();

	UFUNCTION()
	void OnDragonClicked();

	    // сглаженное значение HP (0..1)
    float HPPercentSmoothed = 1.0f;

    float GetHeroHPPercent() const; // вычислить HP (0..1)
};

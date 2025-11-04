// Fill out your copyright notice in the Description page of Project Settings.

#include "UI/HudWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

#include "EnemySpawnManager.h"
#include "Entities/Hero.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"


void UHudWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	if (ButtonGoblin)
		ButtonGoblin->OnClicked.AddDynamic(this, &UHudWidgetBase::OnGoblinClicked);
	if (ButtonVampire)
		ButtonVampire->OnClicked.AddDynamic(this, &UHudWidgetBase::OnVampireClicked);
	if (ButtonDragon)
		ButtonDragon->OnClicked.AddDynamic(this, &UHudWidgetBase::OnDragonClicked);

    if (UWorld* World = GetWorld())
    {
        if (AActor* Found = UGameplayStatics::GetActorOfClass(World, AEnemySpawnManager::StaticClass()))
        {
            SpawnManager = Cast<AEnemySpawnManager>(Found);
        }
            if (AActor* Found = UGameplayStatics::GetActorOfClass(World, AHero::StaticClass()))
        {
            HeroRef = Cast<AHero>(Found);
        }
    }
}



void UHudWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
    if (!SpawnManager) return;

    auto SetCooldownUI = [&](int32 SlotIndex, UButton* Btn, UTextBlock* TextWhenReady, const FText& ReadyLabel)
    {
        
        const bool bReady = SpawnManager->IsSlotReady(SlotIndex);
        if (Btn) Btn->SetIsEnabled(bReady);

        
        if (TextWhenReady)
        {
            if (bReady)
            {
                TextWhenReady->SetText(ReadyLabel);
            }
            else
            {
                const float cd = SpawnManager->GetRemainingCooldown(SlotIndex);
                FNumberFormattingOptions Opts;
                Opts.MaximumFractionalDigits = 1;
                Opts.MinimumFractionalDigits = 1;
                const FText Secs = FText::AsNumber(FMath::Max(0.f, cd), &Opts);
                TextWhenReady->SetText(FText::Format(FText::FromString("{0}s"), Secs));
            }
        }
    };
    
    if (ProgressBarHP)
    {
        const float TargetHP = GetHeroHPPercent(); // 0..1
        if (bSmoothHP)
        {
            HPPercentSmoothed = FMath::FInterpTo(HPPercentSmoothed, TargetHP, InDeltaTime, HPSmoothSpeed);
            ProgressBarHP->SetPercent(HPPercentSmoothed);
        }
        else
        {
            ProgressBarHP->SetPercent(TargetHP);
        }
    }

    SetCooldownUI(0, ButtonGoblin,  GoblinText,  GoblinReadyText);
    SetCooldownUI(1, ButtonVampire, VampireText, VampireReadyText);
    SetCooldownUI(2, ButtonDragon,  DragonText,  DragonReadyText);
}

float UHudWidgetBase::GetHeroHPPercent() const
{
    if (!HeroRef) return 1.f;
    const float cur = HeroRef->Stats.CurrentHP;
    const float max = FMath::Max(1.f, HeroRef->Stats.CurrentMaxHP);
    return FMath::Clamp(cur / max, 0.f, 1.f);
}


void UHudWidgetBase::OnGoblinClicked()
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("Goblin clicked"));
    if (!SpawnManager) { UE_LOG(LogTemp, Warning, TEXT("SpawnManager is null")); return; }

    const int32 SlotIndex = 0;
    if (!SpawnManager->TrySpawnBySlot(SlotIndex))
    {
        const float Cd = SpawnManager->GetRemainingCooldown(SlotIndex);
        UE_LOG(LogTemp, Warning, TEXT("Goblin spawn failed. CD=%.2f, EnemyClass set?"), Cd);
    }
}

void UHudWidgetBase::OnVampireClicked()
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("Vampire clicked"));
    if (!SpawnManager) { UE_LOG(LogTemp, Warning, TEXT("SpawnManager is null")); return; }

    const int32 SlotIndex = 1;
    if (!SpawnManager->TrySpawnBySlot(SlotIndex))
    {
        const float Cd = SpawnManager->GetRemainingCooldown(SlotIndex);
        UE_LOG(LogTemp, Warning, TEXT("Vampire spawn failed. CD=%.2f, EnemyClass set?"), Cd);
    }
}

void UHudWidgetBase::OnDragonClicked()
{
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Magenta, TEXT("Dragon clicked"));
    if (!SpawnManager) { UE_LOG(LogTemp, Warning, TEXT("SpawnManager is null")); return; }

    const int32 SlotIndex = 2;
    if (!SpawnManager->TrySpawnBySlot(SlotIndex))
    {
        const float Cd = SpawnManager->GetRemainingCooldown(SlotIndex);
        UE_LOG(LogTemp, Warning, TEXT("Dragon spawn failed. CD=%.2f, EnemyClass set?"), Cd);
    }
}

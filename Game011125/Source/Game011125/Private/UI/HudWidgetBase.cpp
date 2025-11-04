// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HudWidgetBase.h"

void UHudWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	if (ButtonGoblin)
		ButtonGoblin->OnClicked.AddDynamic(this, &UHudWidgetBase::OnGoblinClicked);
	if (ButtonVampire)
		ButtonVampire->OnClicked.AddDynamic(this, &UHudWidgetBase::OnVampireClicked);
	if (ButtonDragon)
		ButtonDragon->OnClicked.AddDynamic(this, &UHudWidgetBase::OnDragonClicked);
}

void UHudWidgetBase::OnGoblinClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, "Goblin clicked");
}

void UHudWidgetBase::OnVampireClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, "Vampire clicked");
}

void UHudWidgetBase::OnDragonClicked()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Magenta, "Dragon clicked");
}

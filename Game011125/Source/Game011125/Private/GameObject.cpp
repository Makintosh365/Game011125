// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObject.h"

AGameObject::AGameObject()
{
	PrimaryActorTick.bCanEverTick = true;
}


//--------------------------------------------------------------------------
// --- Инициализация при появлении в мире
void AGameObject::BeginPlay()
{
    Super::BeginPlay();

    Stats.ResetHP();
}


void AGameObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

//--------------------------------------------------------------------------
// --- Смерть объекта (по умолчанию просто уничтожаем)
void AGameObject::OnDeath_Implementation()
{
    Destroy();
}


AGameObject::~AGameObject()
{
}

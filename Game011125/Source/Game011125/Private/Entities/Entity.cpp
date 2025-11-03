// Fill out your copyright notice in the Description page of Project Settings.

#include "Entities/Entity.h"

#include "Abilities/Ability.h"
#include "Buffs/Buff.h"
// Sets default values
AEntity::AEntity()
{

}

bool AEntity::UseCurrentAbility()
{
    for (UAbility* ability : abilities)
    {
        if (ability && ability->IsReady())
        {
            ability->Use();
            return true;
        }
    }

    return false;
}

bool AEntity::TakeDamage(float damage)
{
    if (damage <= 0.0f)
    {
        return false;
    }

    Stats.CurrentHP = FMath::Clamp(Stats.CurrentHP - damage, 0.0f, Stats.CurrentMaxHP);

    if (Stats.CurrentHP <= 0.0f)
    {
        OnDeath();
    }

    return true;
}

bool AEntity::UseBuff()
{
    float maxHpMul  = 1.0f;
    float speedMul  = 1.0f;
    float damageMul = 1.0f;

    for (const UBuff* Buff : ActiveBuffs)
    {
        if (!Buff)
        {
            continue;
        }

        maxHpMul  += Buff->hpBonus;     
        speedMul  += Buff->speedBonus;  
        damageMul += Buff->damageBonus; 
    }

    Stats.CurrentMaxHP  = Stats.BaseMaxHP * maxHpMul;
    Stats.CurrentSpeed  = Stats.BaseSpeed * speedMul;
    Stats.CurrentDamage = Stats.BaseDamage * damageMul;

    return ActiveBuffs.Num() > 0;
}

void AEntity::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    for (TObjectPtr<UAbility> ability : abilities)
    {
        if (ability)
            ability->Tick(DeltaTime);
    }
}

void AEntity::BeginPlay()
{
    Super::BeginPlay();
    
    for (TSubclassOf<UAbility> abilityClass : DefaultAbilities)
        abilities.Add(NewObject<UAbility>(this, abilityClass));
}

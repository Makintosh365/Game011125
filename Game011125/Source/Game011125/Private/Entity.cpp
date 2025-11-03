// Fill out your copyright notice in the Description page of Project Settings.

#include "Entity.h"

#include "Ability.h"
#include "Buff.h"
// Sets default values
AEntity::AEntity()
{

}

bool AEntity::UseCurrentAbility()
{

    for (UAbility* Ability : Abilities)
    {
        if (Ability && Ability->IsReady())
        {
            Ability->Use();
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

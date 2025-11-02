#pragma once

#include "CoreMinimal.h"
#include "Stats.generated.h"


USTRUCT(BlueprintType)
struct FStats
{
    GENERATED_BODY()

public:

    //--------------------------------------------------------------------------
    // --- Base values (defined by unit type / class)
    //--------------------------------------------------------------------------

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
    float BaseMaxHP = 100.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
    float BaseDamage = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stats")
    float BaseSpeed = 400.f;

    //--------------------------------------------------------------------------
    // --- Current values (actual values used in combat)
    //--------------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentMaxHP = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentHP = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentSpeed = 400.f;


    //----------------------------------------------------------------------
    // --- Progression / XP
    //----------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|XP")
    int32 TotalXP = 0;

    // текущий уровень юнита
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|XP")
    int32 Level = 1;

    // сколько опыта даст убийство Ё“ќ√ќ юнита
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats|XP")
    int32 XPRewardOnDeath = 10;

    // Restore HP to current max value
    void ResetHP()
    {
        CurrentHP = CurrentMaxHP;
    }

};
// Default player stats
static inline FStats MakePlayerDefaultStats()
{
    FStats S;
    S.BaseMaxHP = 120.f;
    S.CurrentMaxHP = 120.f;
    S.CurrentHP = 120.f;
    S.BaseDamage = 15.f;
    S.CurrentDamage = 15.f;
    S.BaseSpeed = 500.f;
    S.CurrentSpeed = 500.f;

 
    S.TotalXP = 0;
    S.Level = 1;
    S.XPRewardOnDeath = 0; 

    return S;
}

// Default enemy stats
static inline FStats MakeEnemyDefaultStats()
{
    FStats S;
    S.BaseMaxHP = 60.f;
    S.CurrentMaxHP = 60.f;
    S.CurrentHP = 60.f;
    S.BaseDamage = 7.f;
    S.CurrentDamage = 7.f;
    S.BaseSpeed = 250.f;
    S.CurrentSpeed = 250.f;

    S.TotalXP = 0;       
    S.Level = 1;
    S.XPRewardOnDeath = 15; 

    return S;
}
s
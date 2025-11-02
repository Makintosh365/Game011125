#pragma once

#include "CoreMinimal.h"
#include "Stats.generated.h"

// Структура характеристик игрового объекта
USTRUCT(BlueprintType)
struct FStats
{
    GENERATED_BODY()

public:

//--------------------------------------------------------------------------
// --- Базовые значения (то, что задаёт тип юнита)
//--------------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float BaseMaxHP = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float BaseDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float BaseSpeed = 400.f;

//--------------------------------------------------------------------------
// --- Текущие значения (то, что реально сейчас в бою)
//--------------------------------------------------------------------------

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentMaxHP = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentHP = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentDamage = 10.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    float CurrentSpeed = 400.f;

    // Восстановить здоровье до максимума
    void ResetHP()
    {
        CurrentHP = CurrentMaxHP;
    }

};

static inline FStats MakePlayerDefaultStats() //  дефолтные значения
{
    FStats S;
    S.BaseMaxHP = 120.f;
    S.CurrentMaxHP = 120.f;
    S.CurrentHP = 120.f;
    S.BaseDamage = 15.f;
    S.CurrentDamage = 15.f;
    S.BaseSpeed = 500.f;
    S.CurrentSpeed = 500.f;
    S.bIsAlive = true;
    return S;
}

static inline FStats MakeEnemyDefaultStats() // дефолтные значения
{
    FStats S;
    S.BaseMaxHP = 60.f;
    S.CurrentMaxHP = 60.f;
    S.CurrentHP = 60.f;
    S.BaseDamage = 7.f;
    S.CurrentDamage = 7.f;
    S.BaseSpeed = 250.f;
    S.CurrentSpeed = 250.f;
    S.bIsAlive = true;
    return S;
}
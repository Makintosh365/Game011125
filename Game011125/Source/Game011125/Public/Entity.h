#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"

#include "Interfaces/ICanUseAbilities.h"
#include "Interfaces/ICanTakeDamage.h"
#include "Interfaces/ICanUseAbilities.h"
#include "Interfaces/ICanUseBuffs.h"

#include "Entity.generated.h"

class UAbility;
class UBuff;

UCLASS(Abstract)
class GAME011125_API AEntity 
	: public AGameObject
	, public ICanTakeDamage
	, public ICanUseAbilities
	, public ICanUseBuffs
{

	GENERATED_BODY()

public:
	AEntity();
	// ICanUseAbilities
	bool UseCurrentAbility() override;

	// ICanTakeDamage
	bool TakeDamage(float damage) override;

	// ICanUseBuffs
	bool UseBuff() override;

protected:
	//--------------------------------------------------------------------------
	// --- Abilities
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity|Abilities")
	TArray<TObjectPtr<UAbility>> Abilities;

	//--------------------------------------------------------------------------
	// --- Buffs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity|Buffs")
	TArray<TObjectPtr<UBuff>> ActiveBuffs;
};

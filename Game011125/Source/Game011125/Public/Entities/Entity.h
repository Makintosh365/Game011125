#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"
#include "Components/CapsuleComponent.h"

#include "Interfaces/ICanUseAbilities.h"
#include "Interfaces/ICanTakeDamage.h"
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
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Default Values")
	TObjectPtr<UCapsuleComponent> CollisionComponent;
	
	//--------------------------------------------------------------------------
	// --- Abilities
	UPROPERTY(EditAnywhere, Category = "Entity|Abilities")
	TArray<TSubclassOf<UAbility>> DefaultAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, BlueprintReadWrite, Category = "Entity|Abilities")
	TSubclassOf<AGameObject> TargetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity|Abilities")
	TSet<TSubclassOf<AGameObject>> DamagedClasses;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "Entity|Abilities")
	TArray<TObjectPtr<UAbility>> abilities;

	//--------------------------------------------------------------------------
	// --- Buffs
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity|Buffs")
	TArray<TObjectPtr<UBuff>> ActiveBuffs;
};

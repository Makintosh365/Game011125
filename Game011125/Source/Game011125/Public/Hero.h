#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Hero.generated.h"

UCLASS(Abstract, Blueprintable)
class GAME011125_API AHero : public AEntity
{
	GENERATED_BODY()

public:

	AHero();

	static AHero* GetCurrentHero() { return CurrentHero; }

protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	static AHero* CurrentHero;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

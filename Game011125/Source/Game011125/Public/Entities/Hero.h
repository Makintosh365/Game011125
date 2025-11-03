#pragma once

#include "CoreMinimal.h"
#include "Entity.h"
#include "Hero.generated.h"

class ATargetPoint;

/**
 * Hero that moves only along manually assigned ATargetPoint waypoints.
 * - No autoscan, no camera, no extra systems.
 * - Player never controls it.
 * - Super::Tick is NOT called to avoid external side-effects.
 */
UCLASS(Blueprintable)
class GAME011125_API AHero : public AEntity
{
    GENERATED_BODY()

public:
    AHero();

    UFUNCTION(BlueprintCallable, Category = "Hero")
    static AHero* GetCurrentHero() { return CurrentHero; }

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    // Assign TargetPoint actors here (in instance Details). Order in array = path order.
    UPROPERTY(EditInstanceOnly, Category = "Hero|Path")
    TArray<TObjectPtr<ATargetPoint>> Waypoints;

    // Loop back to the first point after the last
    UPROPERTY(EditAnywhere, Category = "Hero|Path")
    bool bLoopPath = true;

    // Distance at which the current point is considered reached
    UPROPERTY(EditAnywhere, Category = "Hero|Path", meta = (ClampMin = "0.0"))
    float AcceptRadius = 150.f;

    // Turn speed toward the next point (deg/sec)
    UPROPERTY(EditAnywhere, Category = "Hero|Movement", meta = (ClampMin = "0.0"))
    float TurnRateDegPerSec = 180.f;

    int32 CurrentIndex = 0;
    static AHero* CurrentHero;

    ATargetPoint* GetCurrentPoint() const;
    void AdvanceIndex();
};

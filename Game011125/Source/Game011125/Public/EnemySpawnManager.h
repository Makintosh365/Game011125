// EnemySpawnManager.h
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnManager.generated.h"

class AHero;

USTRUCT(BlueprintType)
struct FEnemySpawnSlot
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
    TSubclassOf<AActor> EnemyClass = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
    int32 CountPerClick = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cooldown")
    float Cooldown = 3.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Cooldown")
    float NextReadyTime = 0.0f;
};

USTRUCT(BlueprintType)
struct FPeriodicSpawnRule
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Periodic")
    TSubclassOf<AActor> EnemyClass = nullptr;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Periodic")
    int32 CountPerTick = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Periodic", meta=(ClampMin="0.05"))
    float IntervalSeconds = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Periodic", meta=(ClampMin="0.0"))
    float StartDelaySeconds = 0.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Periodic")
    bool bEnabled = false;
};

UCLASS()
class AEnemySpawnManager : public AActor
{
    GENERATED_BODY()

public:
    AEnemySpawnManager();
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="Spawn")
    bool TrySpawnBySlot(int32 SlotIndex);

    UFUNCTION(BlueprintCallable, Category="Spawn")
    float GetRemainingCooldown(int32 SlotIndex) const;

    UFUNCTION(BlueprintCallable, Category="Spawn")
    void SetHero(AHero* InHero);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
    TArray<FEnemySpawnSlot> Slots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Periodic")
    TArray<FPeriodicSpawnRule> PeriodicRules;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Shape")
    float MinDistance = 300.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Shape")
    float MaxDistance = 800.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Shape")
    float HalfAngleDeg = 60.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Nav")
    int32 TriesPerEnemy = 12;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Nav")
    bool bProjectOnNavMesh = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Nav")
    bool bAdjustToGround = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Nav")
    float GroundTraceDistance = 2000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn|Nav")
    TEnumAsByte<ECollisionChannel> GroundTraceChannel = ECC_WorldStatic;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
    bool bDrawDebug = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Debug")
    float DebugTime = 2.f;

private:
    UPROPERTY(Transient)
    AHero* Hero = nullptr;

    UPROPERTY(Transient)
    TArray<FTimerHandle> PeriodicTimerHandles;

    bool IsSlotReady(int32 SlotIndex) const;
    bool GetHeroForwardTransform(FVector& OutLocation, FRotator& OutRotation) const;

    bool FindSpawnPointInFront(const FVector& Origin, const FRotator& Facing, FVector& OutPoint) const;

    bool ProjectToNavMeshIfNeeded(const FVector& InPoint, FVector& OutPoint) const;
    void AdjustToGroundIfNeeded(FVector& InOutPoint) const;

    void DebugDrawPoint(const FVector& P, FColor Color) const;

    int32 SpawnEnemiesOfClass(TSubclassOf<AActor> EnemyClass, int32 Count);

    void StartPeriodicTimers();
    void OnPeriodicSpawnTick(int32 RuleIndex);
};

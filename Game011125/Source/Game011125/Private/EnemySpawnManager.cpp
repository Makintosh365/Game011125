// EnemySpawnManager.cpp

#ifndef ENEMYMANAGER_USE_NAV
#define ENEMYMANAGER_USE_NAV 0
#endif

#include "EnemySpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Pawn.h"
#include "TimerManager.h"

#include "Entities/Hero.h"

#if ENEMYMANAGER_USE_NAV
#include "NavigationSystem.h"
#endif

AEnemySpawnManager::AEnemySpawnManager()
{
    PrimaryActorTick.bCanEverTick = false;

    Slots.SetNum(2);
    Slots[0].CountPerClick = 1;
    Slots[0].Cooldown = 3.f;
    Slots[1].CountPerClick = 3;
    Slots[1].Cooldown = 5.f;

    PeriodicRules.SetNum(1);
    PeriodicRules[0].CountPerTick = 1;
    PeriodicRules[0].IntervalSeconds = 5.0f;
    PeriodicRules[0].StartDelaySeconds = 0.0f;
    PeriodicRules[0].bEnabled = false;

    bProjectOnNavMesh = false;
}

void AEnemySpawnManager::BeginPlay()
{
    Super::BeginPlay();

    if (!Hero)
    {
        AActor* Found = UGameplayStatics::GetActorOfClass(GetWorld(), AHero::StaticClass());
        Hero = Cast<AHero>(Found);
    }

    StartPeriodicTimers();
}

void AEnemySpawnManager::SetHero(AHero* InHero)
{
    Hero = InHero;
}


bool AEnemySpawnManager::IsSlotReady(int32 SlotIndex) const
{
    if (!Slots.IsValidIndex(SlotIndex)) return false;
    const float Now = GetWorld()->TimeSeconds;
    return Now >= Slots[SlotIndex].NextReadyTime;
}

float AEnemySpawnManager::GetRemainingCooldown(int32 SlotIndex) const
{
    if (!Slots.IsValidIndex(SlotIndex)) return -1.f;
    const float Now = GetWorld()->TimeSeconds;
    return FMath::Max(0.f, Slots[SlotIndex].NextReadyTime - Now);
}

bool AEnemySpawnManager::GetHeroForwardTransform(FVector& OutLocation, FRotator& OutRotation) const
{
    if (Hero && IsValid(Hero))
    {
        OutLocation = Hero->GetActorLocation();
        OutRotation = Hero->GetActorRotation();
        return true;
    }
    if (APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
    {
        OutLocation = Pawn->GetActorLocation();
        OutRotation = Pawn->GetActorRotation();
        return true;
    }
    return false;
}

bool AEnemySpawnManager::TrySpawnBySlot(int32 SlotIndex)
{
    if (!Slots.IsValidIndex(SlotIndex)) return false;
    FEnemySpawnSlot& Slot = Slots[SlotIndex];

    if (!IsSlotReady(SlotIndex)) return false;
    if (!Slot.EnemyClass) return false;

    const int32 Spawned = SpawnEnemiesOfClass(Slot.EnemyClass, Slot.CountPerClick);
    if (Spawned > 0)
    {
        Slot.NextReadyTime = GetWorld()->TimeSeconds + Slot.Cooldown;
        return true;
    }
    return false;
}

int32 AEnemySpawnManager::SpawnEnemiesOfClass(TSubclassOf<AActor> EnemyClass, int32 Count)
{
    if (!EnemyClass) return 0;

    FVector Origin; FRotator Facing;
    if (!GetHeroForwardTransform(Origin, Facing)) return 0;

    int32 Spawned = 0;

    for (int32 i = 0; i < Count; ++i)
    {
        bool bDone = false;

        for (int32 t = 0; t < TriesPerEnemy; ++t)
        {
            FVector Candidate;
            if (!FindSpawnPointInFront(Origin, Facing, Candidate))
                continue;

            FVector FinalPoint = Candidate;

            if (bProjectOnNavMesh)
            {
                if (!ProjectToNavMeshIfNeeded(FinalPoint, FinalPoint))
                    continue;
            }

            if (bAdjustToGround)
            {
                AdjustToGroundIfNeeded(FinalPoint);
            }

            FActorSpawnParameters Params;
            Params.SpawnCollisionHandlingOverride =
                ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

            if (AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(EnemyClass, FinalPoint, Facing, Params))
            {
                DebugDrawPoint(FinalPoint, FColor::Green);
                ++Spawned;
                bDone = true;
                break;
            }
        }

        if (!bDone)
        {
            DebugDrawPoint(Origin, FColor::Red);
        }
    }

    return Spawned;
}

bool AEnemySpawnManager::FindSpawnPointInFront(const FVector& Origin, const FRotator& Facing, FVector& OutPoint) const
{
    const float AngleDeg = FMath::RandRange(-HalfAngleDeg, HalfAngleDeg);
    const float Dist = FMath::RandRange(MinDistance, MaxDistance);

    const FRotator YawRot(0.f, AngleDeg, 0.f);
    const FVector Dir = YawRot.RotateVector(Facing.Vector());

    OutPoint = Origin + Dir * Dist;

    if (bDrawDebug)
    {
        DrawDebugLine(GetWorld(), Origin, OutPoint, FColor::Cyan, false, DebugTime, 0, 1.5f);
    }
    return true;
}

bool AEnemySpawnManager::ProjectToNavMeshIfNeeded(const FVector& InPoint, FVector& OutPoint) const
{
#if ENEMYMANAGER_USE_NAV
    if (UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld()))
    {
        FNavLocation Projected;
        const float R = 200.f;
        if (NavSys->ProjectPointToNavigation(InPoint, Projected, FVector(R, R, R)))
        {
            OutPoint = Projected.Location;
            return true;
        }
        return false;
    }
    OutPoint = InPoint;
    return true;
#else
    OutPoint = InPoint;
    return true;
#endif
}

void AEnemySpawnManager::AdjustToGroundIfNeeded(FVector& InOutPoint) const
{
    if (!bAdjustToGround) return;

    const FVector Start = InOutPoint + FVector(0,0,GroundTraceDistance*0.5f);
    const FVector End   = InOutPoint - FVector(0,0,GroundTraceDistance);

    FHitResult Hit;
    FCollisionQueryParams Params(NAME_None, false, this);

    if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, GroundTraceChannel, Params))
    {
        InOutPoint.Z = Hit.ImpactPoint.Z;
        if (bDrawDebug)
        {
            DrawDebugLine(GetWorld(), Start, Hit.ImpactPoint, FColor::Yellow, false, DebugTime, 0, 1.0f);
            DrawDebugPoint(GetWorld(), Hit.ImpactPoint, 12.f, FColor::Yellow, false, DebugTime);
        }
    }
}

void AEnemySpawnManager::DebugDrawPoint(const FVector& P, FColor Color) const
{
    if (!bDrawDebug) return;
    DrawDebugSphere(GetWorld(), P, 20.f, 12, Color, false, DebugTime, 0, 1.5f);
}

// ===== Periodic =====

void AEnemySpawnManager::StartPeriodicTimers()
{
    PeriodicTimerHandles.SetNum(PeriodicRules.Num());

    for (int32 i = 0; i < PeriodicRules.Num(); ++i)
    {
        const FPeriodicSpawnRule& Rule = PeriodicRules[i];
        if (!Rule.bEnabled || !Rule.EnemyClass || Rule.IntervalSeconds <= 0.f)
        {
            continue;
        }

        FTimerDelegate Del;
        Del.BindUObject(this, &AEnemySpawnManager::OnPeriodicSpawnTick, i);

        GetWorldTimerManager().SetTimer(
            PeriodicTimerHandles[i],
            Del,
            Rule.IntervalSeconds,
            true,
            FMath::Max(0.f, Rule.StartDelaySeconds)
        );
    }
}

void AEnemySpawnManager::OnPeriodicSpawnTick(int32 RuleIndex)
{
    if (!PeriodicRules.IsValidIndex(RuleIndex)) return;
    const FPeriodicSpawnRule& Rule = PeriodicRules[RuleIndex];
    if (!Rule.bEnabled || !Rule.EnemyClass) return;

    SpawnEnemiesOfClass(Rule.EnemyClass, FMath::Max(1, Rule.CountPerTick));
}

#include "Entities/Hero.h"
#include "Engine/TargetPoint.h"

AHero* AHero::CurrentHero = nullptr;

AHero::AHero()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AHero::BeginPlay()
{
    Super::BeginPlay();
    CurrentHero = this;

    if (Waypoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("AHero: Waypoints is empty. Assign ATargetPoint actors in the Hero instance Details."));
    }

    CurrentIndex = Waypoints.Num() > 0 ? FMath::Clamp(CurrentIndex, 0, Waypoints.Num() - 1) : 0;
}

void AHero::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (CurrentHero == this)
    {
        CurrentHero = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

void AHero::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    ATargetPoint* Target = GetCurrentPoint();
    if (!Target) return;

    const FVector MyLoc = GetActorLocation();
    const FVector TargetLoc = Target->GetActorLocation();

    FVector ToTarget = TargetLoc - MyLoc;
    const float Dist = ToTarget.Size();

    // Reached this point -> switch to next
    if (Dist <= AcceptRadius)
    {
        AdvanceIndex();
        return;
    }

    if (Dist <= KINDA_SMALL_NUMBER) return;

    // Smoothly turn toward target
    const float DesiredYaw = ToTarget.Rotation().Yaw;
    const float NewYaw = FMath::FixedTurn(GetActorRotation().Yaw, DesiredYaw, TurnRateDegPerSec * DeltaSeconds);
    SetActorRotation(FRotator(0.f, NewYaw, 0.f));

    // Step forward using current speed from stats
    const float Speed = Stats.CurrentSpeed;
    if (Speed <= 0.f) return;

    const FVector Forward = GetActorForwardVector();
    const FVector Delta = Forward * Speed * DeltaSeconds;
    AddActorWorldOffset(Delta, true); // sweep=true to respect collisions
}

ATargetPoint* AHero::GetCurrentPoint() const
{
    if (Waypoints.IsValidIndex(CurrentIndex))
    {
        return Waypoints[CurrentIndex];
    }
    return nullptr;
}

void AHero::AdvanceIndex()
{
    if (Waypoints.Num() == 0) return;

    if (CurrentIndex + 1 < Waypoints.Num())
    {
        ++CurrentIndex;
    }
    else if (bLoopPath)
    {
        CurrentIndex = 0;
    }
    else
    {
        // stop on final point
        Stats.CurrentSpeed = 0.f;
    }
}

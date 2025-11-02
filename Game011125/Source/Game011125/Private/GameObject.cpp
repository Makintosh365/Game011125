
#include "GameObject.h"

AGameObject::AGameObject()
{
    PrimaryActorTick.bCanEverTick = true;
}

AGameObject::~AGameObject() = default;

//--------------------------------------------------------------------------
// --- Called when the game starts or when spawned
void AGameObject::BeginPlay()
{
    Super::BeginPlay();

    Stats.ResetHP();
}

void AGameObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

//--------------------------------------------------------------------------
// --- Default death handler: just destroy the actor
void AGameObject::OnDeath_Implementation()
{
    Destroy();
}
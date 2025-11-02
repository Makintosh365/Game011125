
#include "GameObject.h"

AGameObject::AGameObject()
{
    PrimaryActorTick.bCanEverTick = true;
}

AGameObject::~AGameObject() = default;

//--------------------------------------------------------------------------
// --- Инициализация при появлении в мире
void AGameObject::BeginPlay()
{
    Super::BeginPlay();

    // приводим статы в валидное состояние
    Stats.ResetHP();
}

void AGameObject::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

//--------------------------------------------------------------------------
// --- Смерть объекта (по умолчанию просто уничтожаем)
void AGameObject::OnDeath_Implementation()
{
    Destroy();
}
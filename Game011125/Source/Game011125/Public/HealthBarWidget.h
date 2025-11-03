#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h" //Progress bar HP
#include "HealthBarWidget.generated.h"

/**
 * base class
 */
UCLASS()
class GAME011125_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HP_ProgressBar; //IMPORTANT: variable name = the name of the Progress Bar in the WBP!

	//The function that we will call from PlayerCharacter.cpp
	void SetHealthPercent(float Percent);
};

#include "HealthBarWidget.h"

void UHealthBarWidget::SetHealthPercent(float Percent)
{
	if (HP_ProgressBar)
	{
		//Setting the percentage directly from C++
		HP_ProgressBar->SetPercent(Percent);
	}
}
// Property of Paracosm LLC and Robin Lifshitz.


#include "UI/Widgets/TelegraphDataWidgets/HmDataWidgetSlider.h"

void UHmDataWidgetSlider::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHmDataWidgetSlider::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHmDataWidgetSlider::SetMinSliderValue(float NewValue)
{
	MinSliderValue = NewValue;
}

void UHmDataWidgetSlider::SetMaxSliderValue(float NewValue)
{
	MaxSliderValue = NewValue;
}

void UHmDataWidgetSlider::SetCurrentSliderValue(float NewValue)
{
	CurrentSliderValue = NewValue;
}

void UHmDataWidgetSlider::SetWidgetName(FName NewName)
{
	WidgetName = NewName;
}

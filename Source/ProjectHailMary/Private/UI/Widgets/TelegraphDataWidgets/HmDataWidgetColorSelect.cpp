// Property of Paracosm LLC and Robin Lifshitz.


#include "UI/Widgets/TelegraphDataWidgets/HmDataWidgetColorSelect.h"

void UHmDataWidgetColorSelect::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHmDataWidgetColorSelect::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UHmDataWidgetColorSelect::SetCurrentColor(FString HexString)
{
	FString ColorString = HexString;
	if (ColorString.StartsWith(TEXT("#")))
	{
		ColorString.RemoveAt(0);
	}

	FLinearColor Color;
	Color.InitFromString(ColorString);

	CurrentColor = Color;
}

void UHmDataWidgetColorSelect::SetDefaultColor(FLinearColor Color)
{
	DefaultColor = Color;
}

void UHmDataWidgetColorSelect::SetWidgetName(FName NewName)
{
	WidgetName = NewName;
}


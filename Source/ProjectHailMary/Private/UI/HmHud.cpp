// Property of Paracosm LLC and Robin Lifshitz.


#include "ProjectHailMary/Public/UI/HmHud.h"

#include "Blueprint/UserWidget.h"
#include "UI/Widgets/HmAbilityTelegraphTweaker.h"



void AHmHud::BeginPlay()
{
	Super::BeginPlay();

	//DisplayRuntimeAbilityTweakerWidget();
}

void AHmHud::ShowWidget(UUserWidget* Widget)
{
	if (Widget)
	{
		Widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHmHud::HideWidget(UUserWidget* Widget)
{
	if (Widget && Widget->GetVisibility() == ESlateVisibility::Visible)
	{
		Widget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHmHud::DisplayRuntimeAbilityTweakerWidget()
{
	if (HasAuthority())
	{
		APlayerController* PC = GetOwningPlayerController();
		if (TeleDataWidgetTweakerClass && PC)
		{
			WidgetTweakerRef = Cast<UHmAbilityTelegraphTweaker>(CreateWidget<UUserWidget>(PC, TeleDataWidgetTweakerClass));
			if (WidgetTweakerRef)
			{
				WidgetTweakerRef->AddToViewport(1);
				ShowWidget(WidgetTweakerRef);
			}
		}
	}
}

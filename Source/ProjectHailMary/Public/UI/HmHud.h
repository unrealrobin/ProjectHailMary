// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HmHud.generated.h"

class UHmAbilityTelegraphTweaker;
/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API AHmHud : public AHUD
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UUserWidget> TeleDataWidgetTweakerClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TObjectPtr<UHmAbilityTelegraphTweaker> WidgetTweakerRef;
	
	virtual void BeginPlay() override;

private:

	void ShowWidget(UUserWidget* Widget);
	void HideWidget(UUserWidget* Widget);
};

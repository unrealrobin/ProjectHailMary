// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Characters/HmCharacterBase.h"
#include "GAS/Abilities/HmGA_Base.h"
#include "HmAbilityInfoWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmAbilityInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void AbilityInfoDataApplyToWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Telegraph Data")
	TSubclassOf<AHmCharacterBase> AbilityOwnerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Telegraph Data")
	TSubclassOf<UHmGA_Base> TelegraphedAbilityClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Telegraph Data")
	FName AbilityDataTableRowName;
};

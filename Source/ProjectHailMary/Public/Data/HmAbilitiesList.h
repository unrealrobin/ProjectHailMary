// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataTable.h"
#include "HmAbilitiesList.generated.h"



USTRUCT(BlueprintType)
struct FAbilities : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	TSubclassOf<UGameplayAbility> AbilityOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	TSubclassOf<UGameplayAbility> AbilityTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	TSubclassOf<UGameplayAbility> AbilityThree;
	
};


// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/HmAiBase.h"
#include "Engine/DataTable.h"
#include "GAS/Abilities/HmGA_Base.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmAbilityTelegraphDT.generated.h"

USTRUCT(BlueprintType)
struct FTelegraphData : public FTableRowBase
{
	GENERATED_BODY()

	//Data that populates struct at Runtime
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Telegraph Data")
	FBossAbilityTelegraphData TelegraphData;

	//Can be used for Checks/Gaurds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Telegraph Data")
	TSubclassOf<AHmCharacterBase> CharacterClass;

	//Can be used for Checks/Gaurds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boss Telegraph Data")
	TSubclassOf<UHmGA_Base> TelegraphedAbilityClass = nullptr;
};

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmAbilityTelegraphDT : public UDataTable
{
	GENERATED_BODY()

	FTelegraphData AbilityTelegraphData;
	
};

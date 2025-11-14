// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmGA_Base.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmGA_Base : public UGameplayAbility
{
	GENERATED_BODY()

public:
	/*Provides Safet Checks and Logs Failure*/
	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool CommitChecked();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability TD Row Name")
	FName AbilityTelegraphDataTableRowName = TEXT("NO_NAME_INPUT");

protected:
	//Used for Ability Effects that may have SetByCallerModifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetByCaller Ability Map OPTIONAL")
	TMap<FGameplayTag, float> SetByCallerMap;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FBossAbilityTelegraphData Data;
	
	virtual void ConstructAbilityData(FName AbilityRowName, FBossAbilityTelegraphData &InData) const; 
	
	static FGameplayEffectSpecHandle MakeGESpec(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect> GEClass, float Level = 1.f,const TMap<FGameplayTag, float>* inSetByCallerMap = nullptr);
	
	static void GiveSetByCaller(FGameplayEffectSpecHandle& SpecHandle, const TMap<FGameplayTag, float>& inSetByCallerMap);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph Data Table")
	TObjectPtr<UDataTable> AbilityTelegraphDataTable;
	
};

// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
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

protected:
	//Used for Ability Effects that may have SetByCallerModifiers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SetByCaller Ability Map OPTIONAL")
	TMap<FGameplayTag, float> SetByCallerMap;
	
	static FGameplayEffectSpecHandle MakeGESpec(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect> GEClass, float Level = 1.f,const TMap<FGameplayTag, float>* inSetByCallerMap = nullptr);
	
	static void GiveSetByCaller(FGameplayEffectSpecHandle& SpecHandle, const TMap<FGameplayTag, float>& inSetByCallerMap);
	
};

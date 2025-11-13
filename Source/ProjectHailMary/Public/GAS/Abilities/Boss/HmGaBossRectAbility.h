// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HmGA_Base.h"
#include "Types/BossTelegraphData.h"
#include "HmGaBossRectAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmGaBossRectAbility : public UHmGA_Base
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayEffect> EffectToApplyClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	FBossTelegraphData AbilityData;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
};

// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HmGA_Base.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmGaBossCircleAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmGaBossCircleAbility : public UHmGA_Base
{
	GENERATED_BODY()

public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	FBossAbilityTelegraphData AbilityData;
};

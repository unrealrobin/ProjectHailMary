// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HmGA_Base.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmGaBossRectAbility.generated.h"

class AHmAbilityTelegraphBase;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FBossAbilityTelegraphData AbilityData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<AHmAbilityTelegraphBase> AbilityTelegraphClass;

	UFUNCTION()
	void ApplyEffectToTargets();
	
	UFUNCTION()
	void HandleLock();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

protected:

	UPROPERTY(VisibleAnywhere)
	AHmAbilityTelegraphBase* TelegraphActor = nullptr;
};

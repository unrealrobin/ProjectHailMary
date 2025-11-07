// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "HmGA_Base.h"
#include "HmGA_ShootProjectile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmGA_ShootProjectile : public UHmGA_Base
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayEffect> ProjectileSpawnEffect;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Ability")
	TSubclassOf<AActor> ProjectileToSpawnClass;
};

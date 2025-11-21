// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/HmGA_Base.h"
#include "HmProjectileSpray.generated.h"

class AHmProjectileBase;
/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmProjectileSpray : public UHmGA_Base
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	float DelayBetweenProjectiles = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	int ProjectileAmount = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	TSubclassOf<AHmProjectileBase> ProjectileClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

private:
	FRotator GetSpawnRotation(AActor& ActorRef, int CurrentShot, int TotalShots);

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	int CurrentIteration = 0;

	FTimerHandle DelayedLoopHandle;

	UFUNCTION()
	void FireProjectile();
	
};

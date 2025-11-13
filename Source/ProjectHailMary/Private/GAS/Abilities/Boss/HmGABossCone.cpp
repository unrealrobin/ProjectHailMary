// Property of Paracosm LLC and Robin Lifshitz.


#include "GAS/Abilities/Boss/HmGABossCone.h"

void UHmGABossCone::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Find Target Player

	UE_LOG(LogTemp, Warning, TEXT("Cone Ability Activated."))
	//Spawn Decal Cone Targeting Player


	//Delay


	//Lock Cone position
	

	// Find all players in the cone


	//Apple GE to all players in the cone.

	
	//Cleanup
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UHmGABossCone::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

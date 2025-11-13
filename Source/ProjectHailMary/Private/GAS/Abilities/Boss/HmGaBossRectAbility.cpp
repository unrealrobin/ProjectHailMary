// Property of Paracosm LLC and Robin Lifshitz.


#include "GAS/Abilities/Boss/HmGaBossRectAbility.h"

void UHmGaBossRectAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Find Target Player

	UE_LOG(LogTemp, Warning, TEXT("Rectangle Ability Activated."))
	//Spawn Decal RecTargeting Player 


	//Follow During Delay - Delay


	//Lock Rect position
	

	// Find all players in the cone


	//Apple GE to all players in the cone.

	
	//Cleanup
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UHmGaBossRectAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

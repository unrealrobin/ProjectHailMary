// Property of Paracosm LLC and Robin Lifshitz.


#include "GAS/Abilities/HmGA_Base.h"
#include "AbilitySystemComponent.h"

bool UHmGA_Base::CommitChecked()
{
	if (!CurrentActorInfo) return false;

	/* Ensures no hacks / wierd clients calling ability*/
	const bool bIsAuthority = CurrentActorInfo->IsNetAuthority();
	const bool bIsLocalPred = CurrentActorInfo->IsLocallyControlled();
	if (!bIsAuthority && !bIsLocalPred) return false;

	if (!CanActivateAbility(CurrentSpecHandle, CurrentActorInfo)) return false;
	
	return CommitAbility(CurrentSpecHandle, CurrentActorInfo, GetCurrentActivationInfo(), nullptr);
}

FGameplayEffectSpecHandle UHmGA_Base::MakeGESpec(UAbilitySystemComponent* ASC, TSubclassOf<UGameplayEffect> GEClass, float Level, const TMap<FGameplayTag, float>* inSetByCallerMap)
{
	if (!ASC || !GEClass) return FGameplayEffectSpecHandle();
	
	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GEClass, Level, ASC->MakeEffectContext());

	/* Can be expanded to include the SetSetByCallerMagnitude Extension if Needed.*/
	if (inSetByCallerMap)
	{
		GiveSetByCaller(SpecHandle, *inSetByCallerMap);
	}
	return SpecHandle;
	
}

void UHmGA_Base::GiveSetByCaller(FGameplayEffectSpecHandle& SpecHandle, const TMap<FGameplayTag, float>& inSetByCallerMap)
{
	/* If we have a GE that uses the set by Magnitude Modifer, we add them to the Abilities TMap and then it adds them to the Effect Spec*/
	
	if (!SpecHandle.IsValid()) return;
	for (const auto& Pair : inSetByCallerMap)
	{
		SpecHandle.Data->SetSetByCallerMagnitude(Pair.Key, Pair.Value);
	}
}
	
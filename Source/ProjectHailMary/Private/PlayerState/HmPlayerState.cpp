// Property of Paracosm LLC and Robin Lifshitz.


#include "ProjectHailMary/Public/PlayerState/HmPlayerState.h"
#include "Components/HmAbilitySystemComponent.h"
#include "Components/HmAttributeSet.h"
#include "ProjectHailMary/Data/HmPlayerInitAttributes.h"

AHmPlayerState::AHmPlayerState()
{
	HmAbilitySystemComponent = CreateDefaultSubobject<UHmAbilitySystemComponent>("ASC");
	if (!HmAbilitySystemComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create AbilitySystemComponent"));
	}
	HmAbilitySystemComponent->SetIsReplicated(true);
	HmAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	HmAttributeSet = CreateDefaultSubobject<UHmAttributeSet>("AttributeSet");
	HmAbilitySystemComponent->AddAttributeSetSubobject(HmAttributeSet.Get());
	
}

UAbilitySystemComponent* AHmPlayerState::GetAbilitySystemComponent() const
{
	return HmAbilitySystemComponent;
}

void AHmPlayerState::SetDefaultAttributes_Server()
{
	if (HasAuthority() && IsValid(InitAttributes) && IsValid(DefaultAttributeEffect))
	{
		const FPlayerInitAttributes* Row = InitAttributes->FindRow<FPlayerInitAttributes>(InitAttributesRowName, TEXT("Init"));
		if (Row && HmAttributeSet)
		{
			FGameplayEffectSpecHandle DefaultSpec = HmAbilitySystemComponent->MakeOutgoingSpec(
				DefaultAttributeEffect,
				1.f,
				HmAbilitySystemComponent->MakeEffectContext());

			/*
			 * Tags Required for SetByCaller Modifier
			 * We use this type (SetByCaller) because its dynamic and uses a DT to set the values.
			 */
			FGameplayTag HealthTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.Health");
			FGameplayTag MaxHealthTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.MaxHealth");
			FGameplayTag Speed = FGameplayTag::RequestGameplayTag("SetByCaller.Init.Speed");
			FGameplayTag MaxSpeed = FGameplayTag::RequestGameplayTag("SetByCaller.Init.MaxSpeed");
			
			DefaultSpec.Data->SetSetByCallerMagnitude(HealthTag, Row->Health);
			DefaultSpec.Data->SetSetByCallerMagnitude(MaxHealthTag, Row->MaxHealth);
			DefaultSpec.Data->SetSetByCallerMagnitude(Speed, Row->Speed);
			DefaultSpec.Data->SetSetByCallerMagnitude(MaxSpeed, Row->MaxSpeed);
			
			HmAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DefaultSpec.Data.Get());
			UE_LOG(LogTemp, Warning, TEXT("Initialized Attributes From Data Table."));
			
		}
	}
}

// Property of Paracosm LLC and Robin Lifshitz.


#include "ProjectHailMary/Public/PlayerState/HmPlayerState.h"
#include "Components/HmAbilitySystemComponent.h"
#include "Components/HmAttributeSet.h"
#include "Data/HmPlayerInitAttributes.h"
#include "Data/HmAbilitiesList.h"
#include "Data/PlayerAbiltiesDataAsset.h"

AHmPlayerState::AHmPlayerState()
{
	HmAbilitySystemComponent = CreateDefaultSubobject<UHmAbilitySystemComponent>("ASC");
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
			FGameplayTag SpeedTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.Speed");
			FGameplayTag MaxSpeedTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.MaxSpeed");
			
			DefaultSpec.Data->SetSetByCallerMagnitude(MaxSpeedTag, Row->MaxSpeed);
			DefaultSpec.Data->SetSetByCallerMagnitude(MaxHealthTag, Row->MaxHealth);
			DefaultSpec.Data->SetSetByCallerMagnitude(HealthTag, Row->Health);
			DefaultSpec.Data->SetSetByCallerMagnitude(SpeedTag, Row->Speed);

			/*UE_LOG(LogTemp, Warning, TEXT("Setting Default Attributes MaxSpeed: %f, MaxHealth: %f, Health: %f, Speed: %f"),
								 Row->MaxSpeed,
								 Row->MaxHealth,
								 Row->Health,
								 Row->Speed)*/
			
			
			HmAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*DefaultSpec.Data.Get());
			UE_LOG(LogTemp, Warning, TEXT("Initialized Attributes From Data Table."));
			
		}
	}
}

void AHmPlayerState::GrantInitialAbilities(TSet<FAbilityInputMap> Mappings)
{
	if (!HasAuthority() || !HmAbilitySystemComponent) return;

	// Clear old abilities 
	HmAbilitySystemComponent->ClearAllAbilities();

	// Grant new ones
	int32 InputID = 0;
	for (const FAbilityInputMap& Map : Mappings)
	{
		if (Map.AbilityClass)
		{
			FGameplayAbilitySpec Spec(
				Map.AbilityClass,
				1,           
				InputID++,   // InputID
				this         
			);
			HmAbilitySystemComponent->GiveAbility(Spec);
		}
	}
}

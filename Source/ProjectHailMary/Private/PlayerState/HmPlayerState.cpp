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

void AHmPlayerState::SetInitialAttributesOnAttributeSet_Server()
{
	if (HasAuthority() && IsValid(InitAttributes))
	{
		const FPlayerInitAttributes* Row = InitAttributes->FindRow<FPlayerInitAttributes>(InitAttributesRowName, TEXT("Init"));
		if (Row && HmAttributeSet)
		{
			UE_LOG(LogTemp, Warning, TEXT("Initialized Attributes From Data Table."));
			HmAttributeSet->InitMaxHealth(Row->MaxHealth);
			HmAttributeSet->InitMaxSpeed(Row->MaxSpeed);
			HmAttributeSet->InitHealth(FMath::Clamp(Row->Health, 0.0f, Row->MaxHealth));
			HmAttributeSet->InitSpeed(FMath::Clamp(Row->Speed, 0.0f, Row->MaxSpeed));
		}
	}
}

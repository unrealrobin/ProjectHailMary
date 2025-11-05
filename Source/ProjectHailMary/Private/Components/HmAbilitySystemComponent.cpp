// Property of Paracosm LLC and Robin Lifshitz.


#include "Components/HmAbilitySystemComponent.h"
#include "Characters/HmPlayerCharacter.h"
#include "Components/HmAttributeSet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PlayerState/HmPlayerState.h"

UHmAbilitySystemComponent::UHmAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UHmAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UHmAbilitySystemComponent::InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor)
{
	Super::InitAbilityActorInfo(InOwnerActor, InAvatarActor);

	BindAttributeListeners();
	InitializeDependentAttributes();
}

void UHmAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHmAbilitySystemComponent::BindAttributeListeners()
{
	AHmPlayerState* PS = Cast<AHmPlayerState>(GetOwner());
	if (!IsValid(PS)) return;

	/*Bind functions to Attribute Changes*/
	UE_LOG(LogTemp, Warning, TEXT("Binding Attribute Change Handlers"));
	MoveSpeedHandle = GetGameplayAttributeValueChangeDelegate(PS->HmAttributeSet->GetSpeedAttribute()).AddUObject(this, &UHmAbilitySystemComponent::HandleChangeSpeedAttribute);
}

void UHmAbilitySystemComponent::InitializeDependentAttributes()
{
	/*
	 * Some attributes are used immediately by the Character. This initializes them to the correct
	 * locations as soon as the character is Possessed by the controller.
	 */
	if (ACharacter* CharacterPlayer = Cast<ACharacter>(GetAvatarActor()))
	{
		if (UCharacterMovementComponent* MovementComponent = CharacterPlayer->GetCharacterMovement())
		{
			// Push current Speed -> MaxWalkSpeed
			const float Speed = GetNumericAttribute(UHmAttributeSet::GetSpeedAttribute());
			MovementComponent->MaxWalkSpeed = Speed;
			UE_LOG(LogTemp, Warning, TEXT("Speed: %f"), Speed);
		}
	}
}

void UHmAbilitySystemComponent::HandleChangeSpeedAttribute(const FOnAttributeChangeData& OnAttributeChangeData)
{
	//Handle Changes to the Players movement here.
	AHmPlayerCharacter* Character = Cast<AHmPlayerCharacter>(GetAvatarActor());
	if (!IsValid(Character)) return;
	
	UCharacterMovementComponent* CharacterMovement = Character->GetCharacterMovement();
	if (!IsValid(CharacterMovement)) return;
	
	CharacterMovement->MaxWalkSpeed = FMath::Max(0.0f, OnAttributeChangeData.NewValue);
}


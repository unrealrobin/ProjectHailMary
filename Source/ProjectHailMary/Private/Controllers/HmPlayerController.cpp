// Property of Paracosm LLC and Robin Lifshitz.


#include "Controllers/HmPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/HmPlayerCharacter.h"
#include "Components/HmAbilitySystemComponent.h"
#include "Data/HmAbilitiesList.h"
#include "Data/PlayerAbiltiesDataAsset.h"
#include "PlayerState/HmPlayerState.h"

void AHmPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	CachedOwnedCharacter = Cast<AHmPlayerCharacter>(InPawn);
	if (IsValid(CachedOwnedCharacter))
	{
		ControlledPawnASC = Cast<UHmAbilitySystemComponent>(Cast<AHmPlayerState>(CachedOwnedCharacter->GetPlayerState())->HmAbilitySystemComponent);
		if (!ControlledPawnASC)
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not access the Player State."))
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Player state is Valid."))
		}
		
	}
	
	//Set the Ability System Component to the Pawn.
}

void AHmPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetupInputComponent();
}

void AHmPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	PlayerInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (IsValid(PlayerInputComponent))
	{
		BindActionsToInputComponent();
	}

	if (GetLocalPlayer())
	{
		EnhancedInputSubsystem = GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
		if (EnhancedInputSubsystem)
		{
			EnhancedInputSubsystem->AddMappingContext(StandardInputMappingContext, 0);
		}
	}
	//Bind all Inputs via UInputActions w/ Callback functions.
	
}

void AHmPlayerController::MoveForward(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		FVector ForwardDirection = ControlledPawn->GetActorForwardVector();
		ControlledPawn->AddMovementInput(ForwardDirection, Value.Get<float>());
	}
}

void AHmPlayerController::MoveRight(const FInputActionValue& Value)
{
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn)
	{
		FVector RightDirection = ControlledPawn->GetActorRightVector();
		ControlledPawn->AddMovementInput(RightDirection, Value.Get<float>());
	}
}

void AHmPlayerController::HandleAbilityOneAction(const FInputActionValue& Value)
{
	FGameplayAbilitySpecHandle FoundHandle;
	TSubclassOf<UGameplayAbility> DesiredAbilityClass; /* your ability class */;
	
	if (ControlledPawnASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("ControlledPawnASC Valid on Controller"))
		ControlledPawnASC->AbilityLocalInputPressed(0);

		UDataTable* Row = Cast<AHmPlayerState>(CachedOwnedCharacter->GetPlayerState())->AbilitiesList;
		if (FAbilities* RLine = Row->FindRow<FAbilities>("PlayerInitialAbilities", ""))
		{
			if (RLine->AbilityOne)
			{
				DesiredAbilityClass = RLine->AbilityOne;
			}
		}
	}
	
	for (const FGameplayAbilitySpec& Spec : ControlledPawnASC->GetActivatableAbilities())
	{
		if (Spec.Ability && Spec.Ability->GetClass() == DesiredAbilityClass)
		{
			FoundHandle = Spec.Handle;
			break;
		}
	}
 
	if (FoundHandle.IsValid())
	{
		bool bActivated = ControlledPawnASC->TryActivateAbility(FoundHandle);
		if (bActivated)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ability activated."));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Could not activate ability."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability spec handle not found."));
	}
}

void AHmPlayerController::HandleAbilityTwoAction(const FInputActionValue& Value)
{
	if (ControlledPawnASC)
	{
		ControlledPawnASC->AbilityLocalInputPressed(0);
	}
}

void AHmPlayerController::HandleAbilityThreeAction(const FInputActionValue& Value)
{
	if (ControlledPawnASC)
	{
		ControlledPawnASC->AbilityLocalInputPressed(0);
	}
}

void AHmPlayerController::BindActionsToInputComponent()
{
	if (IsValid(PlayerInputComponent))
	{
		PlayerInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AHmPlayerController::MoveForward);
		PlayerInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AHmPlayerController::MoveRight);
	}

	if (PlayerAbilityDataAsset)
	{
		for (const FAbilityInputMap Mapping: PlayerAbilityDataAsset->Mappings)
		{
			if (Mapping.InputAction && Mapping.InputID != -1)
			{
				PlayerInputComponent->BindAction(Mapping.InputAction, ETriggerEvent::Started,
					this, &AHmPlayerController::InputPressed, Mapping.InputID);

				PlayerInputComponent->BindAction(Mapping.InputAction, ETriggerEvent::Completed,
					this, &AHmPlayerController::InputReleased, Mapping.InputID);
			}
		}
	}
}

void AHmPlayerController::InputPressed(int32 InputId)
{
	if (AHmPlayerState* PS = GetPlayerState<AHmPlayerState>())
	{
		if (UAbilitySystemComponent* ASC =	PS->GetAbilitySystemComponent())
		{
			ASC->AbilityLocalInputPressed(InputId);
		}
	}
}

void AHmPlayerController::InputReleased(int32 InputId)
{
	if (AHmPlayerState* PS = GetPlayerState<AHmPlayerState>())
	{
		if (UAbilitySystemComponent* ASC =	PS->GetAbilitySystemComponent())
		{
			ASC->AbilityLocalInputReleased(InputId);
		}
	}
}



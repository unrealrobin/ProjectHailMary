// Property of Paracosm LLC and Robin Lifshitz.


#include "Controllers/HmPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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


void AHmPlayerController::BindActionsToInputComponent()
{
	if (IsValid(PlayerInputComponent))
	{
		PlayerInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AHmPlayerController::MoveForward);
		PlayerInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AHmPlayerController::MoveRight);
	}
}



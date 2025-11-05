// Property of Paracosm LLC and Robin Lifshitz.

#include "Characters/HmPlayerCharacter.h"
#include "PlayerState/HmPlayerState.h"
#include "Components/HmAbilitySystemComponent.h"
#include "Controllers/HmPlayerController.h"
// Sets default values
AHmPlayerCharacter::AHmPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}
void AHmPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHmPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AHmPlayerCharacter::InitializeAbilitySystemComponent()
{
	/*Called both on the server and the client*/
	
	//When being possessed by the controller, we check the player state and get the ASC from it and store it locally.
	AHmPlayerState* PS = GetPlayerState<AHmPlayerState>();
	if (IsValid(PS))
	{
		ASC = Cast<UHmAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		if (!IsValid(ASC))
		{
			UE_LOG(LogTemp, Error, TEXT("HmPlayerCharacter - PossessedBy() - Failed to get ASC"));
			return;
		}

		//Server and client need this in order for prediction and replication to work
		ASC->InitAbilityActorInfo(PS, this);
	}
}

/*Called on the Server*/
void AHmPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UE_LOG(LogTemp, Warning, TEXT("HmPlayerCharacter - PossessedBy()"));
	

	if (HasAuthority())
	{
		AHmPlayerState* PS = GetPlayerState<AHmPlayerState>();
		if (PS)
		{
			InitializeAbilitySystemComponent();
			//Sets the starting attributes on the server.
			PS->SetInitialAttributesOnAttributeSet_Server();
			
		}
	}
}

//Called on the Client
void AHmPlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	UE_LOG(LogTemp, Warning, TEXT("HmPlayerCharacter - OnRep_PlayerState"));
	InitializeAbilitySystemComponent();

	if (IsLocallyControlled())
	{
		AHmPlayerController* PC = Cast<AHmPlayerController>(GetController());
		if (IsValid(PC))
		{
			//Bind controller to Abilties
		}
	}
}






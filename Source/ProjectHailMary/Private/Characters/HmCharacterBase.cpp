// Property of Paracosm LLC and Robin Lifshitz.


#include "ProjectHailMary/Public/Characters/HmCharacterBase.h"


// Sets default values
AHmCharacterBase::AHmCharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHmCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHmCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


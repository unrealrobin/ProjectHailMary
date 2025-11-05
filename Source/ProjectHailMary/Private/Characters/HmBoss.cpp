// Property of Paracosm LLC and Robin Lifshitz.


#include "HmBoss.h"


// Sets default values
AHmBoss::AHmBoss()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHmBoss::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AHmBoss::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


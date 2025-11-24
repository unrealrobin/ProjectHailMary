// Property of Paracosm LLC and Robin Lifshitz.


#include "Encounters/Coordinator/HmEncounterCoordinator.h"


// Sets default values
AHmEncounterCoordinator::AHmEncounterCoordinator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHmEncounterCoordinator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmEncounterCoordinator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


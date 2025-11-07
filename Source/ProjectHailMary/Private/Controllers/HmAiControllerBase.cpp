// Property of Paracosm LLC and Robin Lifshitz.


#include "Controllers/HmAiControllerBase.h"
// Sets default values
AHmAiControllerBase::AHmAiControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHmAiControllerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmAiControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


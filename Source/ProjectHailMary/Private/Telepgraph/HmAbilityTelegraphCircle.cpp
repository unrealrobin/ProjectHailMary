// Property of Paracosm LLC and Robin Lifshitz.


#include "Telepgraph/HmAbilityTelegraphCircle.h"


// Sets default values
AHmAbilityTelegraphCircle::AHmAbilityTelegraphCircle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHmAbilityTelegraphCircle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmAbilityTelegraphCircle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("SHould be moving."))
	if (IsValid(TargetActor) && !bIsLockedInPlace)
	{
		FVector TargetLocation = TargetActor->GetActorLocation();
		RootComponent->SetWorldLocation(TargetLocation);
	}
}


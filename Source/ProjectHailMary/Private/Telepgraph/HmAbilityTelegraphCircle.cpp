// Property of Paracosm LLC and Robin Lifshitz.


#include "Telepgraph/HmAbilityTelegraphCircle.h"

#include "Components/DecalComponent.h"


// Sets default values
AHmAbilityTelegraphCircle::AHmAbilityTelegraphCircle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AHmAbilityTelegraphCircle::ChangeDecalSize(FVector NewDecalSize)
{
	DecalComponent->DecalSize = NewDecalSize;

	UE_LOG(LogTemp, Warning, TEXT("Changing Decal Size in Circle."))
}

void AHmAbilityTelegraphCircle::HandleSpawnInitializationWithData(FBossAbilityTelegraphData TelegraphData)
{
	Super::HandleSpawnInitializationWithData(TelegraphData);
	FVector DecalSize = FVector(TelegraphData.Radius, TelegraphData.Radius, TelegraphData.Radius);
	ChangeDecalSize(DecalSize);
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
	//UE_LOG(LogTemp, Warning, TEXT("SHould be moving."))
	if (IsValid(TargetActor) && !bIsLockedInPlace)
	{
		FVector TargetLocation = TargetActor->GetActorLocation();
		RootComponent->SetWorldLocation(TargetLocation);
	}
}


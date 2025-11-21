// Property of Paracosm LLC and Robin Lifshitz.


#include "Telepgraph/HmAbilityTelegraphRectangle.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AHmAbilityTelegraphRectangle::AHmAbilityTelegraphRectangle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AHmAbilityTelegraphRectangle::AdjustDecalComponentOffsetLocation(FVector DecalCompSize)
{
	FVector OffsetLocation = FVector(DecalCompSize.X, 0.f, 0.f);
	DecalComponent->SetRelativeLocation(OffsetLocation);
	BoxComponent->SetRelativeLocation(OffsetLocation);
}

// Called when the game starts or when spawned
void AHmAbilityTelegraphRectangle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmAbilityTelegraphRectangle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsValid(TargetActor) && !bIsLockedInPlace)
	{
		FVector RootLocation = RootComponent->GetComponentLocation();
		FVector TargetLocation = TargetActor->GetActorLocation();
		FRotator AmountToRotate = UKismetMathLibrary::FindLookAtRotation(RootLocation, TargetLocation);
		RootComponent->SetRelativeRotation(AmountToRotate);
	}
}


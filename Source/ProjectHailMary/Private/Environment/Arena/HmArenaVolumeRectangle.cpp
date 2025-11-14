// Property of Paracosm LLC and Robin Lifshitz.


#include "Environment/Arena/HmArenaVolumeRectangle.h"

#include "Components/BoxComponent.h"


// Sets default values
AHmArenaVolumeRectangle::AHmArenaVolumeRectangle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ArenaBox = CreateDefaultSubobject<UBoxComponent>("ArenaBox");
	RootComponent = ArenaBox;

	ArenaBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

float AHmArenaVolumeRectangle::GetBoxFloorZ() const
{
	//Used to quickly get the arenas floor height
	if (ArenaBox)
	{
		return ArenaBox->GetComponentLocation().Z - ArenaBox->GetScaledBoxExtent().Z; 
	}

	UE_LOG(LogTemp, Warning, TEXT("Could not get a valid ref to ArenaBox."))
	return 0.f;
}

FVector AHmArenaVolumeRectangle::GetArenaCenter() const
{
	if (ArenaBox)
	{
		return ArenaBox->GetComponentLocation();
	}

	return FVector::ZeroVector;
}

void AHmArenaVolumeRectangle::GetArenaCorners(TArray<FVector>& OutCorners) const
{
	//Returns an array of the 4 corners of the arena
	OutCorners.Reset(4);

	const FVector C = ArenaBox->GetComponentLocation();
	const FVector E = ArenaBox->GetScaledBoxExtent();
	const float Z = GetBoxFloorZ();

	OutCorners.Add(FVector(C.X - E.X, C.Y - E.Y, Z));
	OutCorners.Add(FVector(C.X + E.X, C.Y - E.Y, Z));
	OutCorners.Add(FVector(C.X + E.X, C.Y + E.Y, Z));
	OutCorners.Add(FVector(C.X - E.X, C.Y + E.Y, Z));
	
}

bool AHmArenaVolumeRectangle::IsPointInside2D(const FVector& Point, float Tolerance) const
{
	const FVector C = ArenaBox->GetComponentLocation();
	const FVector E = ArenaBox->GetScaledBoxExtent();
	const bool inX = FMath::Abs(Point.X - C.X) <= (E.X + Tolerance);
	const bool inY = FMath::Abs(Point.Y - C.Y) <= (E.Y + Tolerance);
	return inX && inY;
}


// Called when the game starts or when spawned
void AHmArenaVolumeRectangle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHmArenaVolumeRectangle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Property of Paracosm LLC and Robin Lifshitz.


#include "Telepgraph/HmAbilityTelegraphBase.h"

#include "Components/DecalComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"


void AHmAbilityTelegraphBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHmAbilityTelegraphBase, Data);
}

void AHmAbilityTelegraphBase::OnRep_BossTelegraphData(FBossTelegraphData OldBossTelegraphData)
{
	FVector DecalSize(Data.BoxLength, Data.BoxWidth, Data.BoxHeight);
	ChangeDecalSize(DecalSize);
}

// Sets default values
AHmAbilityTelegraphBase::AHmAbilityTelegraphBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	bAlwaysRelevant = true;
	AActor::SetReplicateMovement(true);       
	SetNetCullDistanceSquared(200000.0f);

	DecalSceneComponent = CreateDefaultSubobject<USceneComponent>("Decal Scene Component");
	RootComponent = DecalSceneComponent;

	DecalComponent = CreateDefaultSubobject<UDecalComponent>("Decal Component");
	DecalComponent->SetupAttachment(RootComponent);
	DecalComponent->SetIsReplicated(true);

	//Will call an initial Location Adjustment, making the Scene Component at the edge of the decal component
	//making the scene component a "Proxy Pivot Point"
	//When then use the scene component to handle rotation of the decal.
	ChangeDecalSize(DecalComponent->DecalSize);

	DecalComponent->SetDecalMaterial(DecalMaterial);
	
}



void AHmAbilityTelegraphBase::ChangeDecalSize(FVector NewDecalSize)
{
	DecalComponent->DecalSize.X = NewDecalSize.X;
	DecalComponent->DecalSize.Y = NewDecalSize.Y;
	DecalComponent->DecalSize.Z = NewDecalSize.Z;

	AdjustDecalComponentOffsetLocation(DecalComponent->DecalSize);
}

// Called when the game starts or when spawned
void AHmAbilityTelegraphBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("telegraph actor spawned."))
	
}

void AHmAbilityTelegraphBase::AdjustDecalComponentOffsetLocation(FVector DecalCompSize)
{
	FVector OffsetLocation = FVector(DecalCompSize.X, 0.f, 0.f);
	DecalComponent->SetRelativeLocation(OffsetLocation);
}

// Called every frame
void AHmAbilityTelegraphBase::Tick(float DeltaTime)
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


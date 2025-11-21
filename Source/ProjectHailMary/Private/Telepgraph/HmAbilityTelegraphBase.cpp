// Property of Paracosm LLC and Robin Lifshitz.


#include "Telepgraph/HmAbilityTelegraphBase.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Net/UnrealNetwork.h"


void AHmAbilityTelegraphBase::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AHmAbilityTelegraphBase, Data);
}

void AHmAbilityTelegraphBase::OnRep_BossTelegraphData(FBossAbilityTelegraphData OldBossTelegraphData)
{
	FVector DecalSize(Data.BoxLength, Data.BoxWidth, Data.BoxHeight);
	ChangeDecalSize(DecalSize);

	UE_LOG(LogTemp, Warning, TEXT("OnRep for Data fired."))
	//Apply Dynamic Material with Colors from Data.
	
	UpdateDynamicMaterialInstance_Client();
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

	/*
	 * Dbug Box
	 */
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Debug Box");
	BoxComponent->SetupAttachment(RootComponent);
	BoxComponent->SetVisibility(true);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	
	//Will call an initial Location Adjustment, making the Scene Component at the edge of the decal component
	//making the scene component a "Proxy Pivot Point"
	//When then use the scene component to handle rotation of the decal.
	//ChangeDecalSize(DecalComponent->DecalSize, true);

	if (DecalMaterial)
	{
		DecalComponent->SetDecalMaterial(DecalMaterial);
	}
	
}

void AHmAbilityTelegraphBase::ChangeDecalSize(FVector NewDecalSize)
{
	DecalComponent->DecalSize.X = NewDecalSize.X;
	DecalComponent->DecalSize.Y = NewDecalSize.Y;
	DecalComponent->DecalSize.Z = NewDecalSize.Z;

	BoxComponent->SetBoxExtent(NewDecalSize);
	
}

// Called when the game starts or when spawned
void AHmAbilityTelegraphBase::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("TelegraphActor BeginPlay on %s"),HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"));
	InitializeDynamicMaterial();
	
}

void AHmAbilityTelegraphBase::AdjustDecalComponentOffsetLocation(FVector DecalCompSize)
{
	FVector OffsetLocation = FVector(DecalCompSize.X, 0.f, 0.f);
	DecalComponent->SetRelativeLocation(OffsetLocation);
	BoxComponent->SetRelativeLocation(OffsetLocation);
}

void AHmAbilityTelegraphBase::InitializeDynamicMaterial()
{
	if (DecalComponent && !DynamicDecalMaterial)
	{
		DynamicDecalMaterial = UMaterialInstanceDynamic::Create(DecalMaterial, this);
		if (DynamicDecalMaterial)
		{
			DecalComponent->SetDecalMaterial(DynamicDecalMaterial);
			//UE_LOG(LogTemp, Warning, TEXT("Dynamic Material is Initialized & Valid. %s"), HasAuthority() ? TEXT("- SERVER") : TEXT("- CLIENT"))
			UpdateDynamicMaterialInstance_Server();
		}
	}
}

void AHmAbilityTelegraphBase::UpdateDynamicMaterialInstance_Server()
{
	if (HasAuthority())
	{
		DynamicDecalMaterial->SetVectorParameterValue("TelegraphColorBase", Data.TelegraphColorBase);
		DynamicDecalMaterial->SetVectorParameterValue("TelegraphColorEmis", Data.TelegraphColorEmis);
		DynamicDecalMaterial->SetScalarParameterValue("TelegraphOpac", Data.TelegraphOpac);
	}
}

void AHmAbilityTelegraphBase::UpdateDynamicMaterialInstance_Client()
{
	if (!HasAuthority())
	{
		if (!DynamicDecalMaterial)
		{
			InitializeDynamicMaterial();
		}
		
		//Are set in the Init Telegraph Data Table Row for the Ability. Can be experimented w/ @ runtime through Encounter Editor.
		DynamicDecalMaterial->SetVectorParameterValue("TelegraphColorBase", Data.TelegraphColorBase);
		DynamicDecalMaterial->SetVectorParameterValue("TelegraphColorEmis", Data.TelegraphColorEmis);
		DynamicDecalMaterial->SetScalarParameterValue("TelegraphOpac", Data.TelegraphOpac);
	}

	UE_LOG(LogTemp, Warning, TEXT("TelegraphActor UpdateDynamicMaterialInstance Color on %s"),HasAuthority() ? TEXT("SERVER") : TEXT("CLIENT"));
	
}

void AHmAbilityTelegraphBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Property of Paracosm LLC and Robin Lifshitz.


#include "Telepgraph/DevelopmentOnly/HmTelegraphCache_Rep.h"

#include "Data/HmAbilityTelegraphDT.h"
#include "Net/UnrealNetwork.h"
#include "Types/BossAbilityTelegraphData.h"


// Sets default values
AHmTelegraphCache_Rep::AHmTelegraphCache_Rep()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
}

void AHmTelegraphCache_Rep::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHmTelegraphCache_Rep, TelegraphCacheData);
}

// Called when the game starts or when spawned
void AHmTelegraphCache_Rep::BeginPlay()
{
	Super::BeginPlay();
	FTelegraphData* Row = TelegraphDataDT->FindRow<FTelegraphData>(DataTableRowName, TEXT("RowToEdit"));
	if (Row)
	{
		TelegraphCacheData = Row->TelegraphData;
	}
}

void AHmTelegraphCache_Rep::OnRep_TelegraphData()
{
	//Tell the TelegraphActor to update from everywhere.
}

// Called every frame
void AHmTelegraphCache_Rep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


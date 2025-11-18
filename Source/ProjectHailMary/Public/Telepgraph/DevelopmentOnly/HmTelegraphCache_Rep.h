// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmTelegraphCache_Rep.generated.h"


UCLASS()
class PROJECTHAILMARY_API AHmTelegraphCache_Rep : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmTelegraphCache_Rep();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_TelegraphData)
	FBossAbilityTelegraphData TelegraphCacheData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TelegraphDataTable")
	UDataTable* TelegraphDataDT;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TelegraphDataTable")
	FName DataTableRowName;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_TelegraphData();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

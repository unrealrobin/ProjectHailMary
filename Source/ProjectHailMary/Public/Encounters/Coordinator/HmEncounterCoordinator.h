// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HmEncounterCoordinator.generated.h"

UCLASS()
class PROJECTHAILMARY_API AHmEncounterCoordinator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmEncounterCoordinator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

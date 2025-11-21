// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "HmAbilityTelegraphBase.h"
#include "HmAbilityTelegraphRectangle.generated.h"

UCLASS()
class PROJECTHAILMARY_API AHmAbilityTelegraphRectangle : public AHmAbilityTelegraphBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmAbilityTelegraphRectangle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

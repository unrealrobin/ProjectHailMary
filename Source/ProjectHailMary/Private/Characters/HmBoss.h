// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HmCharacterBase.h"
#include "HmBoss.generated.h"

UCLASS()
class PROJECTHAILMARY_API AHmBoss : public AHmCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHmBoss();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

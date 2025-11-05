// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "HmCharacterBase.h"
#include "HmPlayerCharacter.generated.h"

class UHmAbilitySystemComponent;

UCLASS()
class PROJECTHAILMARY_API AHmPlayerCharacter : public AHmCharacterBase
{
	GENERATED_BODY()

public:
	AHmPlayerCharacter();
	void InitializeAbilitySystemComponent();
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(Transient)
	TObjectPtr<UHmAbilitySystemComponent> ASC = nullptr;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/*Server Calls*/
	virtual void PossessedBy(AController* NewController) override;

	/*Client Calls*/
	virtual void OnRep_PlayerState() override;
	
};

// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Characters/HmCharacterBase.h"
#include "HmAiBase.generated.h"

class UGameplayEffect;
class UHmAttributeSet;
class UHmAbilitySystemComponent;

UCLASS()
class PROJECTHAILMARY_API AHmAiBase : public AHmCharacterBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHmAiBase();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	TObjectPtr<UDataTable> InitAttributes = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FName InitAttributesRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* AiTargetSceneComponent;

	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System Component")
	TObjectPtr<UHmAbilitySystemComponent> AiASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System Component")
	TObjectPtr<UHmAttributeSet> AiAttributeSet;

	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void InitializeBossAttributes();

	void InitAttributes_Server();

	
};

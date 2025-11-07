// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "HmPlayerState.generated.h"

class UGameplayEffect;
class UHmPlayerInitAttributes;
class UHmAttributeSet;
class UHmAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API AHmPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

	AHmPlayerState();

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	TObjectPtr<UDataTable> InitAttributes = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TObjectPtr<UDataTable> AbilitiesList = nullptr;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffect;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	FName InitAttributesRowName = FName("Initial");
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TObjectPtr<UHmAbilitySystemComponent> HmAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	TObjectPtr<UHmAttributeSet> HmAttributeSet;

	UFUNCTION()
	void SetDefaultAttributes_Server();

	UFUNCTION()
	void GrantInitialAbilities(TSet<FAbilityInputMap> Mappings);
};

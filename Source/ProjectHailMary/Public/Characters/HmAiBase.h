// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Characters/HmCharacterBase.h"
#include "Encounters/Interfaces/EncounterParticipant.h"
#include "HmAiBase.generated.h"

class AHmArenaVolumeRectangle;
class UBoxComponent;
class UGameplayEffect;
class UHmAttributeSet;
class UHmAbilitySystemComponent;
class UBehaviorTreeComponent;

UCLASS()
class PROJECTHAILMARY_API AHmAiBase : public AHmCharacterBase, public IAbilitySystemInterface, public IEncounterParticipant
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHmAiBase();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	TObjectPtr<UDataTable> InitAttributes = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Abilities")
	TObjectPtr<UDataTable> InitAbilities = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	FName InitAttributesRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	FName InitAbilitiesRowName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
	TSubclassOf<UGameplayEffect> DefaultAttributeEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> AiTargetSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USceneComponent> AiProjectileStartComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UBoxComponent> CollisionBoxComponent;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System Component")
	TObjectPtr<UHmAbilitySystemComponent> AiASC;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System Component")
	TObjectPtr<UHmAttributeSet> AiAttributeSet;

	virtual void PossessedBy(AController* NewController) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<AHmArenaVolumeRectangle> ArenaVolume = nullptr;

private:
	
	void GrantBossAbilities_Server();

	void InitAttributes_Server();

	void GetArenaVolume_Server();

	
};

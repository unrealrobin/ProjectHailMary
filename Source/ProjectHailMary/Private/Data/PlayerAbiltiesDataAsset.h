// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Abilities/GameplayAbility.h"
#include "Engine/DataAsset.h"
#include "PlayerAbiltiesDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInputMap {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSubclassOf<UGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* InputAction;

	UPROPERTY(VisibleAnywhere, Category = "Input")
	int32 InputID = -1;
};

FORCEINLINE uint32 GetTypeHash(const FAbilityInputMap& Map)
{
	return HashCombine(GetTypeHash(Map.AbilityClass), GetTypeHash(Map.InputAction));
}

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UPlayerAbilitiesDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSet<FAbilityInputMap> Mappings;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override {
		Super::PostEditChangeProperty(PropertyChangedEvent);

		if (PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(UPlayerAbilitiesDataAsset, Mappings)) {
			// Auto-assign sequential InputIDs
			int32 ID = 0;
			for (FAbilityInputMap& Map : Mappings) {
				Map.InputID = ID++;
			}
		}
	}
#endif
};

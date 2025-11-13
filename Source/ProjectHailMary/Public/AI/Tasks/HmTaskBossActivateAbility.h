// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HmTaskBossActivateAbility.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmTaskBossActivateAbility : public UBTTaskNode
{
	GENERATED_BODY()
	
	UHmTaskBossActivateAbility();
	
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability Tags")
	FGameplayTagContainer TagsToActivate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UGameplayAbility> AbilityToActivate;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Handle")
	FGameplayAbilitySpecHandle AbilitySpecHandle;
	
	FDelegateHandle GameplayAbilityEndedHandle;
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	virtual void OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, EBTNodeResult::Type TaskResult) override;

	UFUNCTION()
	void OnAbilityEnded(const FAbilityEndedData& EndedData);

protected:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC;

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BTComp;
};

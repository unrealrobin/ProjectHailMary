// Property of Paracosm LLC and Robin Lifshitz.


#include "AI/Tasks/HmTaskBossActivateAbility.h"

#include "AIController.h"
#include "Abilities/GameplayAbility.h"
#include "Characters/HmAiBase.h"
#include "Components/HmAbilitySystemComponent.h"

UHmTaskBossActivateAbility::UHmTaskBossActivateAbility()
{
}

void UHmTaskBossActivateAbility::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);

	//Removes the CallBack Bind when an ability ends.
	if (ASC)
	{
		ASC->OnAbilityEnded.Remove(GameplayAbilityEndedHandle);
	}
}

void UHmTaskBossActivateAbility::OnAbilityEnded(const FAbilityEndedData& EndedData)
{
	UGameplayAbility* Ability = EndedData.AbilityThatEnded;
	if (Ability->GetClass() == AbilityToActivate && !EndedData.bWasCancelled)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ability %s ended successfully."), *Ability->GetName())
		FinishLatentTask(*BTComp, EBTNodeResult::Succeeded);
		return;
	}
	
	FinishLatentTask(*BTComp, EBTNodeResult::Failed);
	
}


EBTNodeResult::Type UHmTaskBossActivateAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	BTComp = &OwnerComp;
	
	AHmAiBase* AiCharacter = Cast<AHmAiBase>(OwnerComp.GetAIOwner()->GetCharacter());
	ASC  = AiCharacter->GetAbilitySystemComponent();
	if (!ASC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task Boss Activate Ability - Could not retrieve ASC."))
		return EBTNodeResult::Failed;
	} 


	FGameplayAbilitySpec* AbilitySpec = ASC->FindAbilitySpecFromClass(AbilityToActivate);
	if (!AbilitySpec)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task Boss Activate Ability - Could not find Ability Spec."))
		return EBTNodeResult::Failed;	
	} 

	AbilitySpecHandle = AbilitySpec->Handle;
	
	GameplayAbilityEndedHandle = ASC->OnAbilityEnded.AddUObject(this, &UHmTaskBossActivateAbility::OnAbilityEnded);
	
	const bool bStarted = ASC->TryActivateAbilityByClass(AbilityToActivate);
	if (!bStarted)
	{
		UE_LOG(LogTemp, Warning, TEXT("Task Boss Activate Ability - Failed to activate Ability."))
		return EBTNodeResult::Failed;	
	}
	
	return EBTNodeResult::InProgress;
}

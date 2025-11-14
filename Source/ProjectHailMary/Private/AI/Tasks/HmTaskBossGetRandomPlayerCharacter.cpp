// Property of Paracosm LLC and Robin Lifshitz.


#include "AI/Tasks/HmTaskBossGetRandomPlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/HmAiBase.h"
#include "Characters/HmPlayerCharacter.h"
#include "Controllers/HmAiControllerBase.h"
#include "Kismet/GameplayStatics.h"

EBTNodeResult::Type UHmTaskBossGetRandomPlayerCharacter::ExecuteTask(UBehaviorTreeComponent& OwnerComp,
                                                                     uint8* NodeMemory)
{

	AHmAiControllerBase* AiController = Cast<AHmAiControllerBase>(OwnerComp.GetAIOwner());
	if (!AiController) return EBTNodeResult::Failed;

	AHmAiBase* AiCharacter = Cast<AHmAiBase>(AiController->GetCharacter());
	if (!AiCharacter) return EBTNodeResult::Failed;

	UBlackboardComponent* BC = OwnerComp.GetBlackboardComponent();
	if (!BC) return EBTNodeResult::Failed;

	
	TArray<AActor*> AllPlayerCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AHmPlayerCharacter::StaticClass(), AllPlayerCharacters);

	if (AllPlayerCharacters.Num() > 0)
	{
		int32 RandIndex = FMath::RandRange(0, AllPlayerCharacters.Num() - 1);
		BC->SetValueAsObject(RandomPlayerCharacterKey.SelectedKeyName, AllPlayerCharacters[RandIndex]);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
	
}

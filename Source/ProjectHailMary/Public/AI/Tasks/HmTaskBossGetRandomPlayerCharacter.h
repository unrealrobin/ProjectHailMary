// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "HmTaskBossGetRandomPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmTaskBossGetRandomPlayerCharacter : public UBTTaskNode
{
	GENERATED_BODY()

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	//Key Name of where to store the Random Player Instance (AActor Type)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blackboard")
	FBlackboardKeySelector RandomPlayerCharacterKey;
};

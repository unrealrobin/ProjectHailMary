// Property of Paracosm LLC and Robin Lifshitz.


#include "Controllers/HmAiControllerBase.h"

#include "BrainComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
// Sets default values
AHmAiControllerBase::AHmAiControllerBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("Behavior Tree Component");
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>("Black Board Component");
}

// Called when the game starts or when spawned
void AHmAiControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AHmAiControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	bool bIsUsingBlackboard = UseBlackboard(BlackboardComponent->GetBlackboardAsset(), BlackboardComponent);
	bool bIsRunningBehaviorTree = RunBehaviorTree(BehaviorTreeComponent->GetCurrentTree());

	if (!bIsUsingBlackboard)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Boss Controller - Not Using Blackboard."))
	}

	if (!bIsRunningBehaviorTree)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Boss Controller - Not Running Behavior Tree."))
	}

	if (BrainComponent)
	{
		BrainComponent->StartLogic();
	}
}

// Called every frame
void AHmAiControllerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


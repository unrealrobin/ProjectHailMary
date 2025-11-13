// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HmAiControllerBase.generated.h"

class UBehaviorTreeComponent;

UCLASS()
class PROJECTHAILMARY_API AHmAiControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmAiControllerBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior Tree")
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior Tree")
	UBlackboardComponent* BlackboardComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

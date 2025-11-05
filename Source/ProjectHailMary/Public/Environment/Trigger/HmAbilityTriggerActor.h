// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HmAbilityTriggerActor.generated.h"

class UGameplayEffect;
class UCapsuleComponent;

UCLASS()
class PROJECTHAILMARY_API AHmAbilityTriggerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmAbilityTriggerActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap Capsule")
	TObjectPtr<UCapsuleComponent> OverlapCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	TObjectPtr<UStaticMeshComponent> TriggerMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Triggered Ability Class")
	TSubclassOf<UGameplayEffect> TriggeredEffectClass;

	

protected:
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

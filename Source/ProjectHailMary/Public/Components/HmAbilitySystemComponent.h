// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "HmAbilitySystemComponent.generated.h"

struct FOnAttributeChangeData;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTHAILMARY_API UHmAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHmAbilitySystemComponent();

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void InitAbilityActorInfo(AActor* InOwnerActor, AActor* InAvatarActor) override;
	
	void HandleChangeSpeedAttribute(const FOnAttributeChangeData& OnAttributeChangeData);
	
	UFUNCTION()
	void BindAttributeListeners();

private:
	FDelegateHandle MoveSpeedHandle;
};

// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "HmPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API AHmPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UEnhancedInputComponent> PlayerInputComponent; 

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> StandardInputMappingContext;

	/*Input Actions*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveRightAction;
	
private:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void BindActionsToInputComponent();
	

	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputSubsystem;

	/*Input Actions Callbacks*/
};

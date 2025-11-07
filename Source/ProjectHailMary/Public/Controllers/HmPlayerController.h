// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "HmPlayerController.generated.h"

class AHmPlayerCharacter;
class UAbilitySystemComponent;
struct FInputActionValue;
class UInputAction;
class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;
class UPlayerAbilitiesDataAsset;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TObjectPtr<UPlayerAbilitiesDataAsset> PlayerAbilityDataAsset;

	/*Input Actions*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveForwardAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> MoveRightAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> AbilityOneAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> AbilityTwoAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> AbilityThreeAction;

	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cache")
	TObjectPtr<UAbilitySystemComponent> ControlledPawnASC;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cache")
	TObjectPtr<AHmPlayerCharacter> CachedOwnedCharacter;
	
private:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	void BindActionsToInputComponent();

	//Automatic Input Mappings for GA's
	void InputPressed(int32 InputId);
	void InputReleased(int32 InputId);
	
	void MoveForward(const FInputActionValue& Value);
	void MoveRight(const FInputActionValue& Value);
	void HandleAbilityOneAction(const FInputActionValue& Value);
	void HandleAbilityTwoAction(const FInputActionValue& Value);
	void HandleAbilityThreeAction(const FInputActionValue& Value);
	
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> EnhancedInputSubsystem;

	/*Input Actions Callbacks*/
};

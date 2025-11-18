// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HmDataWidgetColorSelect.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmDataWidgetColorSelect : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* TweakerWidgetRef;
	
	UFUNCTION(BlueprintCallable)
	void SetCurrentColor(FString HexString);
	UFUNCTION(BlueprintCallable)
	void SetDefaultColor(FLinearColor Color);
	UFUNCTION(BlueprintCallable)
	void SetWidgetName(FName NewName);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ApplyNewDataToWidget();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetNewWidgetName(){return WidgetName;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FLinearColor GetCurrentColor(){return CurrentColor;}

	UFUNCTION(BlueprintCallable)
	FORCEINLINE FLinearColor GetDefaultColor(){return DefaultColor;}

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
	FLinearColor CurrentColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
	FLinearColor DefaultColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slider")
	FName WidgetName;
};

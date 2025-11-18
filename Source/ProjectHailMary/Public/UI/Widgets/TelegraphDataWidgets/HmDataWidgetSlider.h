// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HmDataWidgetSlider.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmDataWidgetSlider : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;

	void SetMinSliderValue(float NewValue);
	void SetMaxSliderValue(float NewValue);
	void SetCurrentSliderValue(float NewValue);
	void SetWidgetName(FName NewName);

	UFUNCTION(BlueprintImplementableEvent)
	void SliderApplyNewDataToWidget();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UUserWidget* TweakerWidgetRef;

	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetNewSliderValue() const { return CurrentSliderValue; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FName GetNewWidgetName() const { return WidgetName; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetNewMinSliderValue() const { return MinSliderValue; }
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetNewMaxSliderValue() const { return MaxSliderValue; }
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slider", meta=(AllowPrivateAccess = "true"))
	float MinSliderValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slider", meta=(AllowPrivateAccess = "true"))
	float MaxSliderValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slider", meta=(AllowPrivateAccess = "true"))
	float CurrentSliderValue;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slider", meta=(AllowPrivateAccess = "true"))
	FName WidgetName;
};

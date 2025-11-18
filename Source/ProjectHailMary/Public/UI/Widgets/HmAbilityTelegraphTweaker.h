// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/HmAbilityTelegraphDT.h"
#include "HmAbilityTelegraphTweaker.generated.h"

class AHmTelegraphCache_Rep;
class UHmGA_Base;
class AHmCharacterBase;
class UVerticalBox;
class UHmAbilityTelegraphDT;
/**
 * This widget is to be used during development only and is to be excluded from shipping build.
 * DEVELOPMENT ONLY
 */
UCLASS()
class PROJECTHAILMARY_API UHmAbilityTelegraphTweaker : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	TObjectPtr<UDataTable> TelegraphTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	FName TelegraphRowName;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VertTelegraphBox;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VertAbilityInfo;

	UPROPERTY(VisibleAnywhere)
	AHmTelegraphCache_Rep* TelegraphDataCache;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	TSubclassOf<UUserWidget> ColorWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	TSubclassOf<UUserWidget> SliderWidgetClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	TSubclassOf<UUserWidget> AbilityInfoWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	FBossAbilityTelegraphData WidgetUpdateValues;

	UFUNCTION(BlueprintCallable)
	void PackageData_Float(FName WidgetName, float inNewValue, UPARAM(ref) FBossAbilityTelegraphData& Data);

	UFUNCTION(BlueprintCallable)
	void PackageData_Color(FName WidgetName, FLinearColor inNewValue, UPARAM(ref) FBossAbilityTelegraphData& Data);

	UFUNCTION(BlueprintCallable)
	void UpdateCacheActorStruct(UPARAM(ref) FBossAbilityTelegraphData& Data);
private:
	UFUNCTION()
	void CreateWidgetsFromDataTable();
	void CreateAbilityInfoWidgetFromDataTable(TSubclassOf<AHmCharacterBase> CharacterClass, TSubclassOf<UHmGA_Base> TelegraphedAbilityClass, FName RowName);
	void CreateSliderWidget(FName WidgetName, float MinValue, float MaxValue, float InValue);
	void CreateColorWidget(FName WidgetName, FLinearColor ColorFromTable);
};

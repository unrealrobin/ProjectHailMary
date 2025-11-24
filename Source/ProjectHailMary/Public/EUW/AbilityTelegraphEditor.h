// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Components/DetailsView.h"
#include "Editor/Blutility/Classes/EditorUtilityWidget.h"
#include "Types/BossAbilityTelegraphData.h"
#include "AbilityTelegraphEditor.generated.h"

class AHmAbilityTelegraphBase;
/**
 *  
 */
UCLASS(BlueprintType, Blueprintable)
class PROJECTHAILMARY_API UAbilityTelegraphEditor : public UEditorUtilityWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget)) 
	UDetailsView* MyDetailsViewWidget; 

	UFUNCTION(BlueprintCallable, CallInEditor)
	void RefreshFromDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Telegraph")
	TSubclassOf<AHmAbilityTelegraphBase> TelegraphClass;

	UPROPERTY(BlueprintReadOnly, Category = "Ability Telegraph")
	UDataTable* TelegraphDataTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability Telegraph")
	FBossAbilityTelegraphData TelegraphData;
};

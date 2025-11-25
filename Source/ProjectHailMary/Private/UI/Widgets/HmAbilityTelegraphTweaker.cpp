// Property of Paracosm LLC and Robin Lifshitz.


#include "UI/Widgets/HmAbilityTelegraphTweaker.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "Data/HmAbilityTelegraphDT.h"
#include "Kismet/GameplayStatics.h"
#include "Telepgraph/DevelopmentOnly/HmTelegraphCache_Rep.h"
#include "UI/Widgets/TelegraphDataWidgets/HmAbilityInfoWidget.h"
#include "UI/Widgets/TelegraphDataWidgets/HmDataWidgetColorSelect.h"
#include "UI/Widgets/TelegraphDataWidgets/HmDataWidgetSlider.h"

void UHmAbilityTelegraphTweaker::NativePreConstruct()
{
	Super::NativePreConstruct();
	CreateWidgetsFromDataTable();
}


void UHmAbilityTelegraphTweaker::PackageData_Float(FName WidgetName, float inNewValue, FBossAbilityTelegraphData& Data)
{
	if (WidgetName == "T. Opacity")
	{
		Data.TelegraphOpac = inNewValue;
		return;
	}
	if (WidgetName == "Box Height")
	{
		Data.BoxHeight = inNewValue;
		return;
	}
	if (WidgetName == "Box Width")
	{
		Data.BoxWidth = inNewValue;
		return;
	}
	if (WidgetName == "Box Length")
	{
		Data.BoxLength = inNewValue;
		return;
	}
	if (WidgetName == "Follow Time")
	{
		Data.FollowTime = inNewValue;
		return;
	}
	if (WidgetName == "Lock Time")
	{
		Data.LockTime = inNewValue;
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Float Widget Name not Valid."))
}

void UHmAbilityTelegraphTweaker::PackageData_Color(FName WidgetName, FLinearColor inNewValue, FBossAbilityTelegraphData& Data)
{
	if (WidgetName == "Color Base")
	{
		Data.TelegraphColorBase = inNewValue;
		return;
	}
	if (WidgetName == "Emissive Color")
	{
		Data.TelegraphColorEmis = inNewValue;
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Color Widget Name not Valid."))
}

void UHmAbilityTelegraphTweaker::UpdateCacheActorStruct(FBossAbilityTelegraphData& Data)
{
	//we need to update the struct that is used by the ability.
	if (!TelegraphDataCache)
	{
		TelegraphDataCache = Cast<AHmTelegraphCache_Rep>(UGameplayStatics::GetActorOfClass(GetWorld(), AHmTelegraphCache_Rep::StaticClass()));
	}

	if (TelegraphDataCache)
	{
		TelegraphDataCache->TelegraphCacheData = Data;
	}
	
}

void UHmAbilityTelegraphTweaker::CreateWidgetsFromDataTable()
{
	if (TelegraphTable)
	{
		//Pointer to the Row containing a Struct of Telegraph Data & Some Boss Info.
		FTelegraphData* Row = TelegraphTable->FindRow<FTelegraphData>(TelegraphRowName, TEXT("RowToEdit"));
		if (Row && VertTelegraphBox)
		{
			WidgetUpdateValues = Row->TelegraphData;
			//CreateAbilityInfoWidgetFromDataTable(Row->CharacterClass, Row->TelegraphedAbilityClass, TelegraphRowName);
			CreateColorWidget("Color Base", Row->TelegraphData.TelegraphColorBase );
			CreateColorWidget("Emissive Color", Row->TelegraphData.TelegraphColorEmis );
			CreateSliderWidget("T.Opacity", 0.0f, 1.0f, Row->TelegraphData.TelegraphOpac);
			CreateSliderWidget("Follow Time", 0.0f, 20.0f, Row->TelegraphData.FollowTime);
			CreateSliderWidget("Lock Time", 0.0f, 20.0f, Row->TelegraphData.LockTime);
			CreateSliderWidget("Box Height", 0.0f, 1000.0f, Row->TelegraphData.BoxHeight);
			CreateSliderWidget("Box Length", 0.0f, 3000.0f, Row->TelegraphData.BoxLength);
			CreateSliderWidget("Box Width", 0.0f, 1000.0f, Row->TelegraphData.BoxWidth);
		}
	}
}

void UHmAbilityTelegraphTweaker::CreateAbilityInfoWidgetFromDataTable(TSubclassOf<AHmCharacterBase> CharacterClass, TSubclassOf<UHmGA_Base> TelegraphedAbilityClass, FName RowName )
{
	if (AbilityInfoWidgetClass && VertAbilityInfo)
	{
		UHmAbilityInfoWidget* InfoWidget = Cast<UHmAbilityInfoWidget>(CreateWidget<UUserWidget>(this, AbilityInfoWidgetClass));
		InfoWidget->AbilityOwnerClass = CharacterClass;
		InfoWidget->TelegraphedAbilityClass = TelegraphedAbilityClass;
		InfoWidget->AbilityDataTableRowName = RowName;
		InfoWidget->AbilityInfoDataApplyToWidget();
		VertAbilityInfo->AddChildToVerticalBox(InfoWidget);
		InfoWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UHmAbilityTelegraphTweaker::CreateSliderWidget(FName WidgetName, float MinValue, float MaxValue, float InValue)
{
	if (SliderWidgetClass)
	{
		UHmDataWidgetSlider* SliderWidgetRef = Cast<UHmDataWidgetSlider>(CreateWidget<UUserWidget>(this, SliderWidgetClass));
		if (SliderWidgetRef)
		{
			SliderWidgetRef->SetMinSliderValue(MinValue);
			SliderWidgetRef->SetMaxSliderValue(MaxValue);
			SliderWidgetRef->SetCurrentSliderValue(InValue);
			SliderWidgetRef->SetWidgetName(WidgetName);
			SliderWidgetRef->TweakerWidgetRef = this;
			VertTelegraphBox->AddChildToVerticalBox(SliderWidgetRef);
			SliderWidgetRef->SliderApplyNewDataToWidget();
			SliderWidgetRef->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UHmAbilityTelegraphTweaker::CreateColorWidget(FName WidgetName, FLinearColor ColorFromTable)
{
	if (ColorWidgetClass)
	{
		UHmDataWidgetColorSelect* ColorWidget = Cast<UHmDataWidgetColorSelect>(CreateWidget<UUserWidget>(this, ColorWidgetClass));
		if (ColorWidget)
		{
			ColorWidget->SetDefaultColor(ColorFromTable);
			ColorWidget->SetWidgetName(WidgetName);
			ColorWidget->TweakerWidgetRef = this;
			VertTelegraphBox->AddChildToVerticalBox(ColorWidget);
			ColorWidget->ApplyNewDataToWidget();
			ColorWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
}


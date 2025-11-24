// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmEncounterGraphDA.generated.h"

UENUM(BlueprintType)
enum class EEncounterNodeType : uint8
{
	Ability UMETA(DisplayName = "Ability"), // Enum value with display name
	Wait UMETA(DisplayName = "Wait"),
	Default
};

UENUM(BlueprintType)
enum class EEncounterNodeExitMode : uint8
{
	Immediate UMETA(DisplayName = "Immediate"),
	WaitForDuration UMETA(DisplayName = "WaitForDuration"),
	WaitForCallback UMETA(DisplayName = "WaitForCallback"),
	Default
};

USTRUCT(BlueprintType)
struct FEncounterNodeData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Data")
	int NodeID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node Data")
	int NextNodeID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type Data")
	EEncounterNodeType NodeType = EEncounterNodeType::Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Type Data")
	EEncounterNodeExitMode NodeExitType = EEncounterNodeExitMode::Default;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	FBossAbilityTelegraphData AbilityTelegraphData;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	FName AbilityTelepgraphTableRowName = "NO_NAME_SET";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability Data")
	FGameplayTag AbilityTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Wait Data")
	float WaitDuration = 0.f;

};

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmEncounterGraphDA : public UDataAsset
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int EncounterEntryNode = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Encounter Nodes")
	TArray<FEncounterNodeData> EncounterNodes;
};

// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "HmPlayerInitAttributes.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInitAttributes : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	float Health = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	float Speed = 300.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Attribute Values")
	float MaxSpeed = 1000.0f;
};

/**
 * 
 */
UCLASS()
class PROJECTHAILMARY_API UHmPlayerInitAttributes : public UDataTable
{
	GENERATED_BODY()

	FPlayerInitAttributes PlayerInitAttributes;
};

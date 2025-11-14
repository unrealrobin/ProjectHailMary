#pragma once

#include "CoreMinimal.h"
#include "BossAbilityTelegraphData.generated.h"

USTRUCT(BlueprintType)
struct FBossAbilityTelegraphData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float AngleDeg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float Radius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float FollowTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float LockTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float OpacityFill;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float OpacityEmpty;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FLinearColor FillColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FLinearColor EmptyColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float BoxLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float BoxWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float BoxHeight;

	FBossAbilityTelegraphData() : AngleDeg(0), Radius(0),
	                              FollowTime(0),
	                              LockTime(0),
	                              OpacityFill(0),
	                              OpacityEmpty(0),
	                              FillColor(FLinearColor::White),
	                              EmptyColor(FLinearColor::Gray),
	                              BoxLength(0),
	                              BoxWidth(0), BoxHeight(0)

	{
	}
};
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
	FLinearColor TelegraphColorBase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FLinearColor TelegraphColorEmis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float TelegraphOpac;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float BoxLength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float BoxWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	float BoxHeight;

	FBossAbilityTelegraphData() : AngleDeg(0), Radius(0),
	                              FollowTime(0),
	                              LockTime(0),
									TelegraphColorBase(FLinearColor::Blue), TelegraphColorEmis(FLinearColor::Blue), TelegraphOpac(1.f),
	                              BoxLength(0),
	                              BoxWidth(0), BoxHeight(0)

	{
	}
};
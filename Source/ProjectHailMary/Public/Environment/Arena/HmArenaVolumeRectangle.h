// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HmArenaVolumeRectangle.generated.h"

class UBoxComponent;

UCLASS()
class PROJECTHAILMARY_API AHmArenaVolumeRectangle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmArenaVolumeRectangle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Arena")
	TObjectPtr<UBoxComponent> ArenaBox;

	UFUNCTION(BlueprintCallable)
	float GetBoxFloorZ() const;

	UFUNCTION(BlueprintCallable)
	FVector GetArenaCenter() const;
	
	UFUNCTION(BlueprintCallable)
	void GetArenaCorners(TArray<FVector>& OutCorners) const;
	
	UFUNCTION(BlueprintCallable)
	bool IsPointInside2D(const FVector& Point, float Tolerance = 0.0f) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};

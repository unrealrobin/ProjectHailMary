// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types/BossAbilityTelegraphData.h"
#include "HmAbilityTelegraphBase.generated.h"


class UBoxComponent;

UCLASS()
class PROJECTHAILMARY_API AHmAbilityTelegraphBase : public AActor
{
	GENERATED_BODY()

public:

	AHmAbilityTelegraphBase();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arena")
	bool bIsLockedInPlace = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arena")
	AActor* TargetActor = nullptr;

	UPROPERTY(ReplicatedUsing = OnRep_BossTelegraphData)
	FBossAbilityTelegraphData Data;

	UFUNCTION()
	void OnRep_BossTelegraphData(FBossAbilityTelegraphData OldBossTelegraphData);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Comp")
	TObjectPtr<USceneComponent> DecalSceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Comp")
	TObjectPtr<UDecalComponent> DecalComponent;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Comp")
	TObjectPtr<UBoxComponent> BoxComponent;
	
	//The Base Material to be added in the Editor
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Material")
	TObjectPtr<UMaterial> DecalMaterial;

	//The Dynamic Material Converter in C++ and Editable via Encounter Graph
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decal Material")
	TObjectPtr<UMaterialInstanceDynamic> DynamicDecalMaterial;

	UFUNCTION()
	void ChangeDecalSize(FVector NewDecalSize);

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void AdjustDecalComponentOffsetLocation(FVector DecalCompSize);

public:

	virtual void Tick(float DeltaTime) override;
};

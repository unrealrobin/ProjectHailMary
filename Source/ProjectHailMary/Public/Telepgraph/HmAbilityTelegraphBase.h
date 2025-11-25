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

	void UpdateRotation_Client();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arena")
	bool bIsLockedInPlace = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Arena")
	AActor* TargetActor = nullptr;

	UPROPERTY(VisibleAnywhere, Category="TelegraphData",ReplicatedUsing = OnRep_BossTelegraphData)
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
	TObjectPtr<UMaterialInstance> DecalMaterial = nullptr;

	//The Dynamic Material Converter in C++ and Editable via Encounter Graph
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Decal Material")
	TObjectPtr<UMaterialInstanceDynamic> DynamicDecalMaterial = nullptr;

	UFUNCTION(BlueprintCallable)
	virtual void HandleSpawnInitializationWithData(FBossAbilityTelegraphData TelegraphData);

	UFUNCTION(BlueprintCallable)
	virtual void ChangeDecalSize(FVector NewDecalSize);
	
	UFUNCTION()
	virtual void AdjustDecalComponentOffsetLocation(FVector DecalCompSize);

	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

private:
	void InitializeDynamicMaterial();
	void UpdateDynamicMaterialInstance_Server();
	void UpdateDynamicMaterialInstance_Client();

};

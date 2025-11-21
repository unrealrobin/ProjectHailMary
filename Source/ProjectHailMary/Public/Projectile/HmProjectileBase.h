// Property of Paracosm LLC and Robin Lifshitz.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HmProjectileBase.generated.h"

struct FGameplayEffectContextHandle;
struct FGameplayTag;
class UAbilitySystemComponent;
class UBoxComponent;
class UProjectileMovementComponent;
class UGameplayEffect;

UCLASS()
class PROJECTHAILMARY_API AHmProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AHmProjectileBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float AutoDestroyTime = 2.0f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollisionComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;


	/*
	 * @params:
	 * SourceASC - The Ability System Component that created this projectile.
	 * GE - The Gameplay Effect to Activate on Hit/Whenever
	 * SBDIn - Any sets mod
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void InitPropsFromGA(UAbilitySystemComponent* SourceASC,
	                     TSubclassOf<UGameplayEffect> GE,
	                     const FGameplayEffectContextHandle& CtxIn);

	UFUNCTION()
	void NoHitDestroy();
protected:

	UFUNCTION()
	void HandleProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult);
	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);	

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
};

// Property of Paracosm LLC and Robin Lifshitz.


#include "Projectile/HmProjectileBase.h"

#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AHmProjectileBase::AHmProjectileBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollisionComponent");
	RootComponent = BoxCollisionComponent;
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMeshComponent");
	ProjectileMeshComponent->SetupAttachment(RootComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}

void AHmProjectileBase::InitPropsFromGA(UAbilitySystemComponent* SourceASC, TSubclassOf<UGameplayEffect> GE,
                                        const FGameplayEffectContextHandle& CtxIn)
{
	//Construct Projectile Params from Input
}

void AHmProjectileBase::HandleProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Overlapped: %s "), *OtherActor->GetName())
}

void AHmProjectileBase::HandleProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Projectile Hit: %s "), *OtherActor->GetName())
}

// Called when the game starts or when spawned
void AHmProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	BoxCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AHmProjectileBase::HandleProjectileOverlap);
	BoxCollisionComponent->OnComponentHit.AddDynamic(this, &AHmProjectileBase::HandleProjectileHit);
}

// Called every frame
void AHmProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


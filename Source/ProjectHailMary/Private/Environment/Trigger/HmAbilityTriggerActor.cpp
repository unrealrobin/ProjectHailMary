// Property of Paracosm LLC and Robin Lifshitz.


#include "Environment/Trigger/HmAbilityTriggerActor.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "Characters/HmPlayerCharacter.h"
#include "Components/CapsuleComponent.h"
#include "PlayerState/HmPlayerState.h"


// Sets default values
AHmAbilityTriggerActor::AHmAbilityTriggerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OverlapCapsule = CreateDefaultSubobject<UCapsuleComponent>("Overlap Capsule");
	RootComponent = OverlapCapsule;

	TriggerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Trigger Mesh");
	TriggerMesh->SetupAttachment(RootComponent);
}

void AHmAbilityTriggerActor::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACharacter* Character = Cast<AHmPlayerCharacter>(OtherActor))
	{
		AHmPlayerState* PS = Character->GetPlayerState<AHmPlayerState>();
		if (!PS) return;

		UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
		if (!ASC) return;

		//Create GE Spec
		FGameplayEffectSpecHandle TriggeredEffectSpecHandle = ASC->MakeOutgoingSpec(
			TriggeredEffectClass,
			1.0f,
			ASC->MakeEffectContext());

		ASC->ApplyGameplayEffectSpecToTarget(*TriggeredEffectSpecHandle.Data.Get(), ASC);
	}
}

// Called when the game starts or when spawned
void AHmAbilityTriggerActor::BeginPlay()
{
	Super::BeginPlay();

	OverlapCapsule->OnComponentBeginOverlap.AddDynamic(this, &AHmAbilityTriggerActor::HandleOverlap);
	
}

// Called every frame
void AHmAbilityTriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Property of Paracosm LLC and Robin Lifshitz.


#include "Characters/HmAiBase.h"

#include "Components/HmAbilitySystemComponent.h"
#include "Components/HmAttributeSet.h"
#include "ProjectHailMary/Data/HmPlayerInitAttributes.h"


struct FPlayerInitAttributes;
// Sets default values
AHmAiBase::AHmAiBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AiASC = CreateDefaultSubobject<UHmAbilitySystemComponent>("Ability System Component");
	AiASC->SetIsReplicated(true);
	AiASC->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AiAttributeSet = CreateDefaultSubobject<UHmAttributeSet>("AttributeSet");
	AiASC->AddAttributeSetSubobject(AiAttributeSet.Get());

	AiTargetSceneComponent = CreateDefaultSubobject<USceneComponent>("Target Scene Component");
	AiTargetSceneComponent->SetupAttachment(RootComponent);
}

void AHmAiBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HasAuthority() && IsValid(AiASC))
	{
		AiASC->InitAbilityActorInfo(this, this);
	}
}

// Called when the game starts or when spawned
void AHmAiBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHmAiBase::InitializeBossAttributes()
{
	//Get Boss Attributes for the Default attributes Data Table Row and Set ont he Attributes Sheet
}

void AHmAiBase::InitAttributes_Server()
{
	if (HasAuthority() && IsValid(InitAttributes) && IsValid(InitAttributes))
	{
		const FPlayerInitAttributes* Row = InitAttributes->FindRow<FPlayerInitAttributes>(FName("Boss"), TEXT("Boss"));
		if (Row && AiAttributeSet)
		{
			FGameplayEffectSpecHandle DefaultSpec = AiASC->MakeOutgoingSpec(
				DefaultAttributeEffectClass,
				1.f,
				AiASC->MakeEffectContext());

			/*
			 * Tags Required for SetByCaller Modifier
			 * We use this type (SetByCaller) because its dynamic and uses a DT to set the values.
			 */
			FGameplayTag HealthTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.Health");
			FGameplayTag MaxHealthTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.MaxHealth");
			FGameplayTag SpeedTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.Speed");
			FGameplayTag MaxSpeedTag = FGameplayTag::RequestGameplayTag("SetByCaller.Init.MaxSpeed");
			
			DefaultSpec.Data->SetSetByCallerMagnitude(MaxSpeedTag, Row->MaxSpeed);
			DefaultSpec.Data->SetSetByCallerMagnitude(MaxHealthTag, Row->MaxHealth);
			DefaultSpec.Data->SetSetByCallerMagnitude(HealthTag, Row->Health);
			DefaultSpec.Data->SetSetByCallerMagnitude(SpeedTag, Row->Speed);

			/*UE_LOG(LogTemp, Warning, TEXT(" Setting Default Attributes MaxSpeed: %f, MaxHealth: %f, Health: %f, Speed: %f"),
								 Row->MaxSpeed,
								 Row->MaxHealth,
								 Row->Health,
								 Row->Speed)*/
			
			
			AiASC->ApplyGameplayEffectSpecToSelf(*DefaultSpec.Data.Get());
			UE_LOG(LogTemp, Warning, TEXT("Initialized Attributes From Data Table."));
			
		}
	}
}

// Called every frame
void AHmAiBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



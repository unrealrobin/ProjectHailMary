// Property of Paracosm LLC and Robin Lifshitz.


#include "Characters/HmAiBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/HmAbilitySystemComponent.h"
#include "Components/HmAttributeSet.h"
#include "Data/HmAbilitiesList.h"
#include "ProjectHailMary/Data/HmPlayerInitAttributes.h"


struct FPlayerInitAttributes;
// Sets default values
AHmAiBase::AHmAiBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBoxComponent = CreateDefaultSubobject<UBoxComponent>("Collision Box Component");
	RootComponent = CollisionBoxComponent;
	if (USkeletalMeshComponent* theMesh = GetMesh())
	{
		theMesh->SetupAttachment(RootComponent);
	}
	if (UCapsuleComponent* Capsule = GetCapsuleComponent())
	{
		Capsule->SetupAttachment(RootComponent);
	}
	
	AiASC = CreateDefaultSubobject<UHmAbilitySystemComponent>("Ability System Component");
	AiASC->SetIsReplicated(true);
	AiASC->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AiAttributeSet = CreateDefaultSubobject<UHmAttributeSet>("AttributeSet");
	AiASC->AddAttributeSetSubobject(AiAttributeSet.Get());

	AiTargetSceneComponent = CreateDefaultSubobject<USceneComponent>("Target Scene Component");
	AiTargetSceneComponent->SetupAttachment(RootComponent);

	
}

UAbilitySystemComponent* AHmAiBase::GetAbilitySystemComponent() const
{
	return AiASC;
}

void AHmAiBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HasAuthority() && IsValid(AiASC))
	{
		//Binding Actor and ASC
		AiASC->InitAbilityActorInfo(this, this);

		//Initializing Attributes from DT (@InitAttributes)
		InitAttributes_Server();

		//Granting Abilities from DT (@InitAbilities)
		GrantBossAbilities_Server();
	}
}

// Called when the game starts or when spawned
void AHmAiBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHmAiBase::GrantBossAbilities_Server()
{
	if (!HasAuthority() || !AiASC || !InitAbilities) return;

	//Clear old abilities 
	AiASC->ClearAllAbilities();

	const FAbilities* Row = InitAbilities->FindRow<FAbilities>(InitAbilitiesRowName, TEXT("Boss"));

	if (Row)
	{
		if (Row->AbilityOne)
		{
			FGameplayAbilitySpec Spec(
				Row->AbilityOne,
				1);

			AiASC->GiveAbility(Spec);

			UE_LOG(LogTemp, Warning, TEXT("Granted Ability 1: %s"), *Row->AbilityOne->GetName());
		}

		if (Row->AbilityTwo)
		{
			FGameplayAbilitySpec Spec(
				Row->AbilityTwo,
				1);

			AiASC->GiveAbility(Spec);

			UE_LOG(LogTemp, Warning, TEXT("Granted Ability 2: %s"), *Row->AbilityTwo->GetName());
		}

		if (Row->AbilityThree)
		{
			FGameplayAbilitySpec Spec(
				Row->AbilityThree,
				1);

			AiASC->GiveAbility(Spec);

			UE_LOG(LogTemp, Warning, TEXT("Granted Ability 3: %s"), *Row->AbilityThree->GetName());
		}
	}
}

void AHmAiBase::InitAttributes_Server()
{
	//Uses a SetByCaller GE. GE_ApplyDefaultAttributes
	//Using a Data Table to Populate the SetByCaller Modifer Values
	if (HasAuthority() && IsValid(InitAttributes) && IsValid(InitAttributes))
	{
		const FPlayerInitAttributes* Row = InitAttributes->FindRow<FPlayerInitAttributes>(InitAttributesRowName, TEXT("Boss"));
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

			UE_LOG(LogTemp, Warning, TEXT(" Setting Default Attributes MaxSpeed: %f, MaxHealth: %f, Health: %f, Speed: %f"),
								 Row->MaxSpeed,
								 Row->MaxHealth,
								 Row->Health,
								 Row->Speed)
			
			
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



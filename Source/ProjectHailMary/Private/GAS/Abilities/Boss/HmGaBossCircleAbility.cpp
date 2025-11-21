// Property of Paracosm LLC and Robin Lifshitz.


#include "GAS/Abilities/Boss/HmGaBossCircleAbility.h"

#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/HmAiBase.h"
#include "Controllers/HmAiControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "Telepgraph/HmAbilityTelegraphBase.h"
#include "Telepgraph/DevelopmentOnly/HmTelegraphCache_Rep.h"

void UHmGaBossCircleAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                             const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo)) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);

	//Boss Character Casting Ability
	AHmAiBase* OwningCharacter = Cast<AHmAiBase>(ActorInfo->OwnerActor);
	if (!OwningCharacter) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);

	//Boss Controller - Needed for BT/BB Access
	AHmAiControllerBase* BossController = Cast<AHmAiControllerBase>(OwningCharacter->GetController());
	if (!BossController) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	
	//Character stored on Boss BT/BB
	AActor* RandomPlayerCharacter = Cast<AActor>(BossController->BlackboardComponent->GetValueAsObject("RandomTargetPlayer"));
	if (!RandomPlayerCharacter) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	

	UE_LOG(LogTemp, Warning, TEXT("Circle Ability Activated."))

	if (AbilityTelegraphClass)
	{
		//Spawn the circle telegraph actor based on the size gathered from the Data Table
		FActorSpawnParameters SpawnParams;

		//Transform for Deferred Spawn
		const FVector TelegraphSpawnLocation = RandomPlayerCharacter->GetActorLocation();
		FRotator TelegraphSpawnRotation = RandomPlayerCharacter->GetActorRotation();
		TelegraphSpawnRotation.Pitch = TelegraphSpawnRotation.Pitch + 90.0f;
		const FTransform T(TelegraphSpawnRotation, TelegraphSpawnLocation);
		
		AActor* DeferredActor = GetWorld()->SpawnActorDeferred<AActor>(AbilityTelegraphClass, T);
		if (!DeferredActor) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		TelegraphActor = Cast<AHmAbilityTelegraphBase>(DeferredActor);
		if (!TelegraphActor) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);

		//Init of Data Struct
		Data = FBossAbilityTelegraphData();

		//TODO:: THis will need some tweaking as only some of the Data Requirements are UnNecessary (Ex. Box height/Width/length)

		//Checking if Telegraph Manager is In World. Simple changing where the Original Data Comes From.
		//Telegraph Manager Actor Data can be modified at runtime.
		//Development
		AHmTelegraphCache_Rep* TelegraphManager = Cast<AHmTelegraphCache_Rep>(UGameplayStatics::GetActorOfClass(GetWorld(), AHmTelegraphCache_Rep::StaticClass()));
		if (TelegraphManager)
		{
			Data = TelegraphManager->TelegraphCacheData;
			TelegraphActor->Data = Data;
		}
		else
		{
			//Uses the Constructed Data Struct from the Data Table.
			//Production
			ConstructAbilityData(AbilityTelegraphDataTableRowName, Data);
			TelegraphActor->Data = Data;
		}

		//Circle Ability has a Circle Telegraph
		FVector DecalSize = FVector(Data.Radius, Data.Radius, Data.Radius);
		TelegraphActor->ChangeDecalSize(DecalSize);

		//Setting the Target on the Telegraoh Instance
		TelegraphActor->TargetActor = RandomPlayerCharacter;
		TelegraphActor->FinishSpawning(T);

		//Starts Following Actor Via Tick of Telegraph Actor.
		UAbilityTask_WaitDelay* FollowTimeDelay = UAbilityTask_WaitDelay::WaitDelay(this, Data.FollowTime);

		if (FollowTimeDelay)
		{
			FollowTimeDelay->OnFinish.AddDynamic(this, &UHmGaBossCircleAbility::HandleLock);
			FollowTimeDelay->ReadyForActivation();
		}
		else
		{
			EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		}
		
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}

}

void UHmGaBossCircleAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UHmGaBossCircleAbility::ApplyEffectToTargets()
{
	if (TelegraphActor)
	{
		TelegraphActor->Destroy();
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHmGaBossCircleAbility::HandleLock()
{
	if (TelegraphActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Telegraph Decal should not move."))
		TelegraphActor->bIsLockedInPlace = true;
		UAbilityTask_WaitDelay* LockedTimeDelay = UAbilityTask_WaitDelay::WaitDelay(this, Data.LockTime);
		LockedTimeDelay->OnFinish.AddDynamic(this, &UHmGaBossCircleAbility::ApplyEffectToTargets);
		LockedTimeDelay->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

// Property of Paracosm LLC and Robin Lifshitz.


#include "GAS/Abilities/Boss/HmGaBossRectAbility.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/HmAiBase.h"
#include "Controllers/HmAiControllerBase.h"
#include "Telepgraph/HmAbilityTelegraphBase.h"

void UHmGaBossRectAbility::ApplyEffectToTargets()
{
	//Eventually we should create a collision box that tracks all enemies within the Decal Area and apply the effect to each enemy.
	if (TelegraphActor)
	{
		TelegraphActor->Destroy();
	}
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UHmGaBossRectAbility::HandleLock()
{
	if (TelegraphActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Telegraph Decal should not move."))
		TelegraphActor->bIsLockedInPlace = true;
		UAbilityTask_WaitDelay* LockedTimeDelay = UAbilityTask_WaitDelay::WaitDelay(this, Data.LockTime);
		LockedTimeDelay->OnFinish.AddDynamic(this, &UHmGaBossRectAbility::ApplyEffectToTargets);
		LockedTimeDelay->ReadyForActivation();
	}
	else
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}

void UHmGaBossRectAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (!HasAuthority(&ActivationInfo)) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	
	UE_LOG(LogTemp, Warning, TEXT("Rectangle Ability Activated."))

	//Boss Character Casting Ability
	AHmAiBase* OwningCharacter = Cast<AHmAiBase>(ActorInfo->OwnerActor);
	if (!OwningCharacter) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);

	//Boss Controller - Needed for BT/BB Access
	AHmAiControllerBase* BossController = Cast<AHmAiControllerBase>(OwningCharacter->GetController());
	if (!BossController) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	
	//Character stored on Boss BT/BB
	AActor* RandomPlayerCharacter = Cast<AActor>(BossController->BlackboardComponent->GetValueAsObject("RandomTargetPlayer"));
	if (!RandomPlayerCharacter) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	
	//Spawn Decal RecTargeting Player 
	if (AbilityTelegraphClass)
	{
		FActorSpawnParameters SpawnParams;
		FVector SpawnLocation = OwningCharacter->GetActorLocation();
		FRotator SpawnRotation = OwningCharacter->GetActorForwardVector().Rotation();
		
		const FTransform T(SpawnRotation, SpawnLocation);
	
		
		//Rotation Will happen in the Telegraph actors Tick function if not locked.
		AActor* DeferredActor = GetWorld()->SpawnActorDeferred<AActor>(AbilityTelegraphClass, T);
		if (!DeferredActor) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		
		TelegraphActor = Cast<AHmAbilityTelegraphBase>(DeferredActor);
		if (!TelegraphActor) EndAbility(Handle, ActorInfo, ActivationInfo, true, true);

		//Data Prep for Telegraph
		Data = FBossTelegraphData();
		Data.BoxLength = 2000.0f;
		Data.BoxWidth = 100.0f;
		Data.BoxHeight = 300.0f;
		Data.FollowTime = 10.0f;
		Data.LockTime = 2.0f;

		//Initializing Defaults on Telegraph Actor
		TelegraphActor->TargetActor = RandomPlayerCharacter;
		TelegraphActor->Data = Data;
		FVector DecalSize = FVector(Data.BoxLength, Data.BoxWidth, Data.BoxHeight);
		TelegraphActor->ChangeDecalSize(DecalSize);
		TelegraphActor->FinishSpawning(T);
		

		//Starts Following Actor Via Tick of Telegraph Actor.
		UAbilityTask_WaitDelay* FollowTimeDelay = UAbilityTask_WaitDelay::WaitDelay(this, 3.0f);

		if (FollowTimeDelay)
		{
			FollowTimeDelay->OnFinish.AddDynamic(this, &UHmGaBossRectAbility::HandleLock);
			FollowTimeDelay->ReadyForActivation();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No TelegraphAbilityClass Set on Ability."))
	}
}

void UHmGaBossRectAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

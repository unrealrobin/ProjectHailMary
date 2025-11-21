// Property of Paracosm LLC and Robin Lifshitz.


#include "GAS/Abilities/Boss/HmProjectileSpray.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/HmAiBase.h"
#include "Controllers/HmAiControllerBase.h"
#include "Projectile/HmProjectileBase.h"


void UHmProjectileSpray::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
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

	if (ProjectileClass)
	{
		GetWorld()->GetTimerManager().SetTimer(DelayedLoopHandle, this, &UHmProjectileSpray::FireProjectile, DelayBetweenProjectiles, true);
	}
	else
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
}

void UHmProjectileSpray::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

FRotator UHmProjectileSpray::GetSpawnRotation(AActor& ActorRef, int CurrentShot, int TotalShots)
{
	AHmAiBase* BossActor = Cast<AHmAiBase>(CurrentActorInfo->AvatarActor);
	FVector RightVector = BossActor->GetActorRightVector();
	FVector UpVector = BossActor->GetActorUpVector();
	float DegreesOffset = 180/TotalShots;
	FVector NewDirection = RightVector.RotateAngleAxis(-(DegreesOffset*CurrentShot), UpVector);
	return NewDirection.Rotation();
}

void UHmProjectileSpray::FireProjectile()
{
	if (CurrentIteration < ProjectileAmount)
	{
		FActorSpawnParameters SpawnParams;
		AHmAiBase* BossActor = Cast<AHmAiBase>(CurrentActorInfo->AvatarActor);
		if (BossActor && BossActor->AiProjectileStartComponent)
		{
			FVector SpawnLocation = BossActor->AiProjectileStartComponent->GetComponentLocation();
			DrawDebugSphere(GetWorld(), SpawnLocation, 40.0f, 24, FColor::Red, true);
			FRotator SpawnRotation = GetSpawnRotation(*GetActorInfo().AvatarActor, CurrentIteration, ProjectileAmount);

			AActor* SpawnedProjectile = GetWorld()->SpawnActor<AHmProjectileBase>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams );
			if (SpawnedProjectile)
			{
				CurrentIteration++;
			}
		}
	}
	else
	{
		DelayedLoopHandle.Invalidate();
		EndAbility(GetCurrentAbilitySpecHandle(), CurrentActorInfo, CurrentActivationInfo, true, false);
	}
}


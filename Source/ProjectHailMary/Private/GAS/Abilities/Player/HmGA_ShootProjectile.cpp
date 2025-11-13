// Property of Paracosm LLC and Robin Lifshitz.

#include "GAS/Abilities/Player/HmGA_ShootProjectile.h"
#include "Characters/HmPlayerCharacter.h"
#include "Projectile/HmProjectileBase.h"

void UHmGA_ShootProjectile::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	if (!CommitChecked())
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
	}
	if (ActorInfo->IsNetAuthority())
	{
		const FVector ProjectileStartLocation = Cast<AHmPlayerCharacter>(ActorInfo->AvatarActor)->ProjectileStartLocationSceneComponent->GetComponentLocation();
		const FRotator ProjectileStartRotation = Cast<AHmPlayerCharacter>(ActorInfo->AvatarActor)->ProjectileStartLocationSceneComponent->GetComponentRotation();
		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = Cast<APawn>(ActorInfo->AvatarActor.Get());
		SpawnParams.Owner = Cast<APawn>(ActorInfo->AvatarActor.Get());
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		FTransform SpawnTransform = FTransform(ProjectileStartRotation, ProjectileStartLocation);
		AHmProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AHmProjectileBase>(ProjectileToSpawnClass, SpawnTransform);
		Projectile->InitPropsFromGA(GetAbilitySystemComponentFromActorInfo(), ProjectileSpawnEffect, MakeEffectContext(CurrentSpecHandle, CurrentActorInfo));
		Projectile->FinishSpawning(SpawnTransform);
	}
	
	
	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}

bool UHmGA_ShootProjectile::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
	const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	UE_LOG(LogTemp, Warning, TEXT("Can Activate Ability function fired in Shoot Projectile."))
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

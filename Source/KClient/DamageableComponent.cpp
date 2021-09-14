#include "DamageableComponent.h"

UDamageableComponent::UDamageableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UDamageableComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDamageableComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (isDead)
	{
		SetComponentTickEnabled(false);
		return;
	}

	shieldRegenerationDelay += DeltaTime;
	if (shieldRegenerationDelay >= shieldRegenerationCooltime && currentShieldPoint < maxShieldPoint)
	{
		shieldRegenerationDelay = 0.0f;
		currentShieldPoint += shieldRegenerationAmount;

		if (currentShieldPoint > maxShieldPoint)
		{
			currentShieldPoint = maxShieldPoint;
		}
	}
}

void UDamageableComponent::Init(const int32 healthPoint, const int32 shieldPoint)
{
	maxHealthPoint = healthPoint;
	currentHealthPoint = maxHealthPoint;

	maxShieldPoint = shieldPoint;
	currentShieldPoint = maxShieldPoint;

	isDead = false;
}

void UDamageableComponent::Reset()
{
	currentHealthPoint = maxHealthPoint;
	currentShieldPoint = maxShieldPoint;
	shieldRegenerationDelay = 0.0f;
	isDead = false;
}

void UDamageableComponent::SetInvincible(bool isActive)
{
	isInvincible = isActive;
}

bool UDamageableComponent::IsInvincible() const
{
	return isInvincible;
}

void UDamageableComponent::ApplyDamage(const int32 damageAmount)
{
	if (damageAmount == 0 || isDead == true)
	{
		return;
	}

	int remainDamageAmount = 0;
	if (currentShieldPoint >= damageAmount)
	{
		currentShieldPoint -= damageAmount;
		return;
	}
	else
	{
		remainDamageAmount = damageAmount - currentShieldPoint;
		currentShieldPoint = 0;
	}

	if (currentHealthPoint - remainDamageAmount > 0)
	{
		currentHealthPoint -= remainDamageAmount;
	}
	else
	{
		currentHealthPoint = 0;
		isDead = true;

		auto const character = Cast<ACharacter>(GetOwner());
		if (character)
		{
			character->bUseControllerRotationYaw = false;
		}
	}
}

void UDamageableComponent::ApplyHeal(const int32 healAmount)
{
	if (healAmount == 0 || isDead == true)
	{
		return;
	}

	if (currentHealthPoint - healAmount <= maxHealthPoint)
	{
		currentHealthPoint += healAmount;
	}
	else
	{
		currentHealthPoint = maxHealthPoint;
	}
}

void UDamageableComponent::RegenerationShield()
{
}

int32 UDamageableComponent::GetCurrentHealthPoint() const
{
	return currentHealthPoint;
}

int32 UDamageableComponent::GetMaxHealthPoint() const
{
	return maxHealthPoint;
}

int32 UDamageableComponent::GetCurrentShieldPoint() const
{
	return currentShieldPoint;
}

int32 UDamageableComponent::GetMaxShieldPoint() const
{
	return maxShieldPoint;
}

bool UDamageableComponent::IsDead() const
{
	return isDead;
}
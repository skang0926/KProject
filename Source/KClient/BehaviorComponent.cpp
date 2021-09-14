#include "BehaviorComponent.h"
#include "Projectile.h"

UBehaviorComponent::UBehaviorComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UBehaviorComponent::Initialize() {

}

void UBehaviorComponent::TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) {
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}

void UMovementBase::Initialize() {
	AProjectile* projectile = GetOwner<AProjectile>();
	movement = projectile->AddComponent<UProjectileMovementComponent>();
	movement->SetUpdatedComponent( projectile->GetCollider() );
	movement->InitialSpeed = projectile->GetInitSpeed();
	movement->MaxSpeed = projectile->GetMaxSpeed();
	movement->ProjectileGravityScale = projectile->GetGravityScale();
}

void UMovementBase::TickComponent( float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction ) {
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}

void UStraightMovement::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) {
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}

void UStraightMovement::SetDirection( const FVector& dir ) {
	if ( movement == nullptr ) {
		return;
	}

	movement->Velocity = dir * movement->InitialSpeed;
}

void UChaseTarget::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) {
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}

void UFindTarget::TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) {
	Super::TickComponent( deltaTime, tickType, thisTickFunction );
}
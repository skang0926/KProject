#pragma once

#include "KClient.h"
#include "BehaviorComponent.generated.h"

/*
TrailEffect
CollisionEffect
AttackOne
RangeAttack;
...
*/

UCLASS(Abstract)
class KCLIENT_API UBehaviorComponent : public UActorComponent {
	GENERATED_BODY()

public:	
	UBehaviorComponent();

	virtual void Initialize();
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;
};

UCLASS(Abstract)
class KCLIENT_API UMovementBase : public UBehaviorComponent {
	GENERATED_BODY()

public:	
	virtual void Initialize() override;
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

protected:
	UProjectileMovementComponent* movement;
};

UCLASS()
class KCLIENT_API UStraightMovement : public UMovementBase {
	GENERATED_BODY()

public:	
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

	void SetDirection( const FVector& dir );
};

UCLASS()
class KCLIENT_API UChaseTarget : public UBehaviorComponent {
	GENERATED_BODY()

public:	
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;
};

UCLASS()
class KCLIENT_API UFindTarget : public UBehaviorComponent {
	GENERATED_BODY()

public:	
	virtual void TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;
};
#pragma once

#include "KClient.h"
#include "Projectile.generated.h"

class UProjectileData;

UCLASS()
class KCLIENT_API AProjectile : public AActor {
	GENERATED_BODY()

public:
	template<typename T> 
	T* AddComponent() {
		if ( !T::StaticClass()->IsChildOf( UActorComponent::StaticClass() ) ) {
			return nullptr;
		}

		T* component = NewObject<T>( this, T::StaticClass(), *( T::StaticClass()->GetName() ) );
		component->RegisterComponent();
		return component;
	}

public:
	AProjectile();

	UFUNCTION()
	void OnDestroy();

	UFUNCTION()
	void OnHit( UPrimitiveComponent* hitComponent, AActor* otherActor, UPrimitiveComponent* otherComponent, FVector normalImpulse, const FHitResult& hit );

	UFUNCTION()
	void OnOverlapBegin( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult );

	UFUNCTION()
	void OnOverlapEnd( UPrimitiveComponent* overlappedComp, AActor* otherActor, UPrimitiveComponent* otherComp, int32 otherBodyIndex );

	virtual void Tick( float deltaTime ) override;
	virtual void Initialize( ESkillType skillType, int32 damage );

	ESkillType					GetUsedSkillType() const;
	ACharacterBase* const		GetShooter() const;
	UStaticMeshComponent* const	GetMesh() const;
	USphereComponent* const		GetCollider() const;

	float GetInitSpeed() const;
	float GetMaxSpeed() const;
	float GetGravityScale() const;

protected:
	virtual void BeginPlay() override;

private:
	void SetupComponent();

protected:
	ESkillType					usedSkillType;
	UStaticMeshComponent*		meshComponent;
	USphereComponent*			collisionComponent;
	UProjectileData* 			commonProperty;
	int32						projectileDamage;
};
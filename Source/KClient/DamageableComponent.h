// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "DamageableComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KCLIENT_API UDamageableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDamageableComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Init(const int32 healthPoint, const int32 shieldPoint);
	void Reset();
	void ApplyDamage(const int32 damageAmount);
	void ApplyHeal(const int32 healAmount);
	void SetInvincible(bool isActive);
	
	UFUNCTION(BlueprintCallable, Category = HP)
	int32 GetCurrentHealthPoint() const;
	UFUNCTION(BlueprintCallable, Category = HP)
	int32 GetMaxHealthPoint() const;

	UFUNCTION(BlueprintCallable, Category = Shield)
	int32 GetCurrentShieldPoint() const;
	UFUNCTION(BlueprintCallable, Category = Shield)
	int32 GetMaxShieldPoint() const;

	bool IsDead() const;
	bool IsInvincible() const;

private:
	void RegenerationShield();

private:
	const int32 shieldRegenerationAmount = 1;
	const float shieldRegenerationCooltime = 0.2f;
	float shieldRegenerationDelay = 0.0f;

	UPROPERTY(VisibleAnywhere, Category = HP)
	int32 currentHealthPoint;
	UPROPERTY(VisibleAnywhere, Category = HP)
	int32 maxHealthPoint;

	UPROPERTY(VisibleAnywhere, Category = Shield)
	int32 currentShieldPoint;
	UPROPERTY(VisibleAnywhere, Category = Shield)
	int32 maxShieldPoint;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool isDead;

	bool isInvincible;

};

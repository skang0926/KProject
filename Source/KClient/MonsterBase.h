// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "CharacterBase.h"
#include "MonsterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMonsterAttackDelegate);
/**
 * 
 */
UCLASS(Abstract)
class KCLIENT_API AMonsterBase : public ACharacterBase
{
	GENERATED_BODY()

public:
	AMonsterBase();
		
	virtual void UseSkill(ESkillType skillType);

	virtual int32 GetBaseDamage() const override;
	void SetLockOnComponent(class ACharacterBase* otherCharacter);

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnMonsterAttackDelegate OnAttackDelegate;

private:
	UPROPERTY(VisibleAnywhere)
	class ULockOnComponent* lockOnComponent;

	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UMonsterStatComponent* monsterStatComponent;
};


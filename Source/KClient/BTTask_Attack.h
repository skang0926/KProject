// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */

struct FBTAttackNodeMemory
{
	int32 attackCount;
	int32 curAttackCount;
	ESkillType skillType;
	class AMonsterBase* ownerMonster;
	class UBehaviorTreeComponent* ownerComponent;
	FTimerHandle timerHandle;
};

UCLASS()
class KCLIENT_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Attack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;

private:
	void TimerTask(FBTAttackNodeMemory* memory);
	uint16 GetInstanceMemorySize() const override;

private:
	UPROPERTY(EditAnywhere, Category = Node)
	int32 attackCount;

	UPROPERTY(EditAnywhere, Category = Skill)
	ESkillType skillType = ESkillType::None;
};

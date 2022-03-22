// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "SkillSystem.h"
#include "MonsterBase.h"
#include "BasicType.h"
#include "MonsterAIController.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = false;

	attackCount = 1;
	NodeName = TEXT("Attack");
}

uint16 UBTTask_Attack::GetInstanceMemorySize() const
{
	return sizeof(FBTAttackNodeMemory);
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	Super::ExecuteTask(ownerComp, nodeMemory);

	AMonsterBase* ownerMonster = dynamic_cast<AMonsterBase*>(ownerComp.GetAIOwner()->GetPawn());
	if (ownerMonster == nullptr)
		return EBTNodeResult::Failed;

	// 스킬이 없을 때, 방어 코드
	USkillBase* attkSkill = ownerMonster->GetSkillSystem()->GetSkill( skillType );
	if ( !attkSkill ) {
		UE_LOG( KP, Error, TEXT( "not found attack skill: %s, %s" ), *EnumToFStr( skillType ), *ownerMonster->GetName() );
		return EBTNodeResult::Failed;
	}

	AMonsterAIController* ownerController = dynamic_cast<AMonsterAIController*>(ownerMonster->GetController());

	FBTAttackNodeMemory* memory = reinterpret_cast<FBTAttackNodeMemory*>(MEMORY_POOL_64()->Alloc());

	FTimerDelegate timerDelegate(FTimerDelegate::CreateUObject
		<UBTTask_Attack, FBTAttackNodeMemory*>
		(this, &UBTTask_Attack::TimerTask, memory));
	memory->ownerComponent = &ownerComp;
	memory->attackCount = attackCount;
	memory->curAttackCount = 0;
	memory->skillType = skillType;
	memory->ownerMonster = ownerMonster;
	memory->ownerComponent = &ownerComp;

	float coolTime = attkSkill->GetCommonProperty().cooldown;

	GetWorld()->GetTimerManager().SetTimer(memory->timerHandle, timerDelegate, coolTime + 0.01f, true, 0.1f);
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TimerTask(FBTAttackNodeMemory* memory)
{
	if (memory->curAttackCount >= memory->attackCount)
	{
		GetWorld()->GetTimerManager().ClearTimer(memory->timerHandle);
		FinishLatentTask(*(memory->ownerComponent), EBTNodeResult::Succeeded);
		MEMORY_POOL_64()->Free(memory);
		return;
	}

	memory->ownerMonster->UseSkill(memory->skillType);
	++memory->curAttackCount;
}

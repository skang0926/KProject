// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_DummyTask.h"
#include "MemoryManager.h"
#include "MonsterBase.h"
#include "MonsterAIController.h"
#include "LevelManager.h"
#include "KProjectGameInstance.h"
#include "KClientGameState.h"
#include "TestMonster.h"


UBTTask_DummyTask::UBTTask_DummyTask()
{
	NodeName = TEXT("DummyTask");
	defaultTaskTime = 5.0f;
	bNotifyTick = false;
	bMemoryPoolUse = true;
}

EBTNodeResult::Type UBTTask_DummyTask::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory)
{
	ATestMonster* ownerMonster = dynamic_cast<ATestMonster*>(ownerComp.GetAIOwner()->GetPawn());
	if (ownerMonster == nullptr)
	{
		return EBTNodeResult::Failed;
	}

	FBTDummyNode* memory;

	if (bMemoryPoolUse)
		memory = reinterpret_cast<FBTDummyNode*>(MEMORY_POOL_64()->Alloc(sizeof(FBTDummyNode)));
	else
		memory = new FBTDummyNode;

	if (memory == nullptr)
	{
		UE_LOG(KP, Error, TEXT("Allocation memory is none"));
		return EBTNodeResult::Failed;
	}
	memory->fowardMoveValue = (rand() % 3) - 1;
	memory->rightMoveValue = (rand() % 3) - 1;
	memory->remainTime = defaultTaskTime + (rand() % 3) - 1;
	memory->ownerComponent = &ownerComp;
	memory->ownerMonster = ownerMonster;

	FTimerDelegate tickTimerDelegate(FTimerDelegate::CreateUObject
		<UBTTask_DummyTask, FBTDummyNode*>
		(this, &UBTTask_DummyTask::TickTimerTask, memory));

	FTimerDelegate exitTimerDelegate(FTimerDelegate::CreateUObject
		<UBTTask_DummyTask, FBTDummyNode*>
		(this, &UBTTask_DummyTask::ExitTask, memory));

	GetWorld()->GetTimerManager().SetTimerForNextTick(tickTimerDelegate);


	GetWorld()->GetTimerManager().SetTimer(memory->timerHandle, exitTimerDelegate, 0.1f, false, memory->remainTime);

	return EBTNodeResult::InProgress;
}


void UBTTask_DummyTask::TickTimerTask(FBTDummyNode* memory)
{
	if (memory->remainTime == 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(memory->timerHandle);
		FinishLatentTask(*(memory->ownerComponent), EBTNodeResult::Succeeded);

		if (bMemoryPoolUse)
		{
			MEMORY_POOL_64()->Free(memory);
		}
		else
		{
			delete memory;
		}

		return;
	}

	memory->ownerMonster->MoveForward(memory->fowardMoveValue);
	memory->ownerMonster->MoveSide(memory->rightMoveValue);

	FTimerDelegate timerDelegate(FTimerDelegate::CreateUObject
	<UBTTask_DummyTask, FBTDummyNode*>
	(this, &UBTTask_DummyTask::TickTimerTask, memory));
	GetWorld()->GetTimerManager().SetTimerForNextTick(timerDelegate);
}

void UBTTask_DummyTask::ExitTask(FBTDummyNode* memory)
{
	memory->remainTime = 0.f;
	return;
}
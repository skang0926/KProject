// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DummyTask.generated.h"

/**
 * 
 */


struct FBTDummyNode
{
	float fowardMoveValue;
	float rightMoveValue;
	float remainTime;
	class ATestMonster* ownerMonster;
	class UBehaviorTreeComponent* ownerComponent;
	FTimerHandle timerHandle;
};

UCLASS()
class KCLIENT_API UBTTask_DummyTask : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_DummyTask();

protected:
	void TickTimerTask(FBTDummyNode* memory);

private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) override;
	void ExitTask(FBTDummyNode* memory);
private:
	UPROPERTY(EditAnywhere)
	float defaultTaskTime;
};

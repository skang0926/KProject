// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "AIController.h"
#include "MonsterAIController.generated.h"
/**
 * 
 */
UCLASS()
class KCLIENT_API AMonsterAIController : public AAIController
{
	GENERATED_BODY()

public:
	AMonsterAIController();
	virtual void OnPossess(APawn* inPawn) final;
	virtual void OnUnPossess() final;

private:
	UPROPERTY()
		class UBehaviorTree* behaviorTreeAsset;

	UPROPERTY()
		class UBlackboardData* blackBoardAsset;

public:
	static const FName homePosKey;
	static const FName targetKey;
};

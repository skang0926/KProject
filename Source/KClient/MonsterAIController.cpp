// Fill out your copyright notice in the Description page of Project Settings.

#include "MonsterAIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackBoardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MonsterBase.h"
#include "CharacterDataTable.h"

const FName AMonsterAIController::homePosKey = FName(TEXT("HomePos"));
const FName AMonsterAIController::targetKey = FName(TEXT("Target"));

AMonsterAIController::AMonsterAIController()
{
	bSetControlRotationFromPawnOrientation = 0;
}

void AMonsterAIController::OnPossess(APawn* inPawn)
{
	Super::OnPossess(inPawn);

	auto ownerMonster = dynamic_cast<AMonsterBase*>(inPawn);
	if (ownerMonster == nullptr) return;
	auto ownerMonsterData = ownerMonster->GetCharacterTableRow();
	

	blackBoardAsset = LoadObject<UBlackboardData>(NULL, CONVERT_TEXT( ownerMonsterData->BBPath ), NULL, LOAD_None, NULL);
	behaviorTreeAsset = LoadObject<UBehaviorTree>(NULL, CONVERT_TEXT( ownerMonsterData->BTPath ), NULL, LOAD_None, NULL);

	if (UseBlackboard(blackBoardAsset, Blackboard))
	{
		Blackboard->SetValueAsVector(homePosKey, ownerMonster->GetActorLocation());
		RunBehaviorTree(behaviorTreeAsset);
	}
}


void AMonsterAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
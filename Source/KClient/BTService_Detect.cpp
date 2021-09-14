// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_Detect.h"
#include "MonsterBase.h"
#include "MonsterAIController.h"
#include "CharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "LockOnComponent.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.f;
}


void UBTService_Detect::TickNode(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory, float deltaSeconds)
{
	Super::TickNode(ownerComp, nodeMemory, deltaSeconds);

	auto controllingPawn = dynamic_cast<AMonsterBase*>(ownerComp.GetAIOwner()->GetPawn());
	if (controllingPawn == nullptr) return;

	UWorld* world = controllingPawn->GetWorld();
	if (world == nullptr) return;

	FVector center = controllingPawn->GetActorLocation();

	TArray<FOverlapResult> overlapResults;
	FCollisionQueryParams collisionQueryParams(NAME_None, false, controllingPawn);
	bool bResult = world->OverlapMultiByChannel(
		overlapResults,
		center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(detectRadius),
		collisionQueryParams
	);

	if (!bResult)
	{
		ownerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::targetKey, nullptr);
		controllingPawn->SetLockOnComponent(nullptr);
		return;
	}

	for (const auto& overlapResult : overlapResults)
	{
		auto otherCharacter = dynamic_cast<ACharacterBase*>(overlapResult.GetActor());
		if (otherCharacter == nullptr) continue;

		if (otherCharacter->GetController() == world->GetFirstPlayerController())
		{
			FHitResult hitResult;
			bool bLineTraceResult = world->LineTraceSingleByChannel(
				hitResult,
				controllingPawn->GetActorLocation(),
				otherCharacter->GetActorLocation(),
				ECollisionChannel::ECC_GameTraceChannel2
			);

			if (!bLineTraceResult)
			{
				ownerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::targetKey, otherCharacter);
				controllingPawn->SetLockOnComponent(otherCharacter);
			}
			else
			{
				ownerComp.GetBlackboardComponent()->SetValueAsObject(AMonsterAIController::targetKey, nullptr);
				controllingPawn->SetLockOnComponent(nullptr);
			}
			break;
		}
	}
}

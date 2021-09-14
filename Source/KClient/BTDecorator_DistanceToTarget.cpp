// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_DistanceToTarget.h"
#include "MonsterAIController.h"
#include "CharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTDecorator_DistanceToTarget::UBTDecorator_DistanceToTarget()
{
	NodeName = TEXT("InDistanceToTarget");
	distance = 0.f;
}

bool UBTDecorator_DistanceToTarget::CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(ownerComp, nodeMemory);

	auto controllingPawn = ownerComp.GetAIOwner()->GetPawn();
	if (controllingPawn == nullptr)
		return false;

	auto target = dynamic_cast<ACharacterBase*>(ownerComp.GetBlackboardComponent()->GetValueAsObject(AMonsterAIController::targetKey));
	if (target == nullptr)
		return false;

	const UBlackboardComponent* myBlackboard = ownerComp.GetBlackboardComponent();

	FVector targetLocation;
	if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Object::StaticClass())
	{
		UObject* keyValue = myBlackboard->GetValue<UBlackboardKeyType_Object>(BlackboardKey.GetSelectedKeyID());
		AActor* targetActor = Cast<AActor>(keyValue);
		targetLocation = targetActor->GetActorLocation();
	}
	else if (BlackboardKey.SelectedKeyType == UBlackboardKeyType_Vector::StaticClass())
	{
		UBlackboardKeyType_Vector::FDataType keyValue = myBlackboard->GetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID());
		targetLocation = keyValue;
	}
	else return false;

	return FVector::Distance(targetLocation, controllingPawn->GetActorLocation()) <= distance;
}
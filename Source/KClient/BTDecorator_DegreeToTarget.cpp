// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_DegreeToTarget.h"
#include "MonsterAIController.h"
#include "CharacterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTDecorator_DegreeToTarget::UBTDecorator_DegreeToTarget()
{
	NodeName = TEXT("InDegreeToTarget");
	degree = 0.f;
}

bool UBTDecorator_DegreeToTarget::CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const
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

	FVector vDir = targetLocation - controllingPawn->GetActorLocation();
	vDir = vDir.GetSafeNormal2D();
	
	FVector forwardVector = controllingPawn->GetActorForwardVector();
	float radian = FVector::DotProduct(forwardVector, vDir);
	float degreeToTarget = FMath::RadiansToDegrees(acos(radian));

	return degreeToTarget <= degree/2;
}
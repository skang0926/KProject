// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_DegreeToTarget.generated.h"

/**
 * 
 */
UCLASS()
class KCLIENT_API UBTDecorator_DegreeToTarget : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTDecorator_DegreeToTarget();

protected:
	bool CalculateRawConditionValue(UBehaviorTreeComponent& ownerComp, uint8* nodeMemory) const override;

private:
	UPROPERTY(EditAnywhere, Category = Node)
	float degree;
};

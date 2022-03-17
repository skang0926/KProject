// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MonsterBase.h"
#include "TestMonster.generated.h"

/**
 * 
 */
UCLASS()
class KCLIENT_API ATestMonster : public AMonsterBase
{
	GENERATED_BODY()
public:
	ATestMonster();

protected:
	virtual void Tick(float deltaTime) final;
	virtual void BeginPlay() final;

private:
};

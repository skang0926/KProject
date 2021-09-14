// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "MonsterBase.h"
#include "NormalMonster.generated.h"

/**
 * 
 */
UCLASS()
class KCLIENT_API ANormalMonster : public AMonsterBase
{
	GENERATED_BODY()
public:
	ANormalMonster();

protected:
	virtual void Tick(float deltaTime) final;
	virtual void BeginPlay() final;

private:

};

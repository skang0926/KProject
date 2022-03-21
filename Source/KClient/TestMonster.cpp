// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster.h"

ATestMonster::ATestMonster()
{
	characterName = TEXT("TestMonster");
}

void ATestMonster::BeginPlay()
{
	Super::BeginPlay();
}

void ATestMonster::MoveForward(const float value)
{
	Super::MoveForward(value);
}

void ATestMonster::MoveSide(const float value)
{
	Super::MoveSide(value);
}


void ATestMonster::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}
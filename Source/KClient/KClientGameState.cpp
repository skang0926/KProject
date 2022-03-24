// Fill out your copyright notice in the Description page of Project Settings.


#include "KClientGameState.h"

void AKClientGameState::SetLevelManager(ALevelManager* const levelManager)
{
	if (levelManager == nullptr)
		return;

	pLevelManager = levelManager;
}

const ALevelManager* const AKClientGameState::GetLevelManager()
{
	return pLevelManager;
}


// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "GameFramework/GameStateBase.h"
#include "LevelManager.h"
#include "KClientGameState.generated.h"

#define GAME_STATE() ( dynamic_cast<AKClientGameState*>( this->GetWorld()->GetGameState() ) )
#define MEMORY_POOL_64() ( GAME_STATE()->GetLevelManager()->GetMemoryManager()->GetMemoryPool64() )
#define MEMORY_POOL_128() ( GAME_STATE()->GetLevelManager()->GetMemoryManager()->GetMemoryPool128() )
#define MEMORY_POOL_256() ( GAME_STATE()->GetLevelManager()->GetMemoryManager()->GetMemoryPool256() )

UCLASS()
class KCLIENT_API AKClientGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	const class ALevelManager* const GetLevelManager();
	void SetLevelManager(ALevelManager* const levelManager);

private:
	const ALevelManager* pLevelManager = nullptr;
};

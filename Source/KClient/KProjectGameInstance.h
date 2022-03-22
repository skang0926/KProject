// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "LevelManager.h"
#include "KProjectGameInstance.generated.h"

#define GAME_INSTANCE() ( dynamic_cast<UKProjectGameInstance*>( this->GetWorld()->GetGameInstance() ) )
#define MEMORY_POOL_64() ( GAME_INSTANCE()->GetLevelManager()->GetMemoryManager()->GetMemoryPool() )

UCLASS()
class KCLIENT_API UKProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UKProjectGameInstance();

	const struct FCharacterTable* const GetCharacterTableRow(const FName& characterName);
	const struct FSkillProperty* const GetSkillTableRow(const FName& skillName);
	const struct FMonsterStat* const GetMonsterStatTableRow(const FName& monsterName);
	const class ALevelManager* const GetLevelManager();
	void SetLevelManager(ALevelManager* const levelManager);
private:
	const UDataTable* characterTable = nullptr;
	const UDataTable* skillPropertyTable = nullptr;
	const UDataTable* monsterStatTable = nullptr;
	const ALevelManager* pLevelManager = nullptr;
};
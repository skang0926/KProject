// Fill out your copyright notice in the Description page of Project Settings.


#include "KProjectGameInstance.h"
#include "SkillBase.h"
#include "CharacterDataTable.h"
#include "MonsterStatComponent.h"
#include "LevelManager.h"

UKProjectGameInstance::UKProjectGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>DT_CHARACTER(CONVERT_TEXT(EStringKey::PATH_DATA_CHARACTER_TABLE));
	if (DT_CHARACTER.Succeeded())
	{
		characterTable = DT_CHARACTER.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable>DT_SKILL(CONVERT_TEXT(EStringKey::PATH_DATA_SKILL_TABLE));
	if (DT_SKILL.Succeeded())
	{
		skillPropertyTable = DT_SKILL.Object;
	}

	static ConstructorHelpers::FObjectFinder<UDataTable>DT_MONSTERSTAT(CONVERT_TEXT(EStringKey::PATH_DATA_MONSTERSTAT_TABLE));
	if (DT_MONSTERSTAT.Succeeded())
	{
		monsterStatTable = DT_MONSTERSTAT.Object;
	}
}

const FCharacterTable* const UKProjectGameInstance::GetCharacterTableRow(const FName& characterName)
{
	return characterTable->FindRow<FCharacterTable>(characterName, FString(), false);
}
const FSkillProperty* const UKProjectGameInstance::GetSkillTableRow(const FName& skillName)
{
	return skillPropertyTable->FindRow<FSkillProperty>(skillName, FString(), false);
}

const FMonsterStat* const UKProjectGameInstance::GetMonsterStatTableRow(const FName& monsterName)
{
	return monsterStatTable->FindRow<FMonsterStat>(monsterName, FString(), false);
}

void UKProjectGameInstance::SetLevelManager(ALevelManager* const levelManager)
{
	if (levelManager == nullptr)
		return;

	pLevelManager = levelManager;
}

const ALevelManager* const UKProjectGameInstance::GetLevelManager()
{
	return pLevelManager;
}


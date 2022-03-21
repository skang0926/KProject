#pragma once

// String.txt와 순서 동일해야함
UENUM(BlueprintType)
enum class EStringKey : uint8 {
	NONE = 0,
	//// UI Text
	
	//// Resource Path
	PATH_MESH_SPHERE,
	PATH_MESH_PLAYER,
	PATH_ANIM_PLAYER,
	PATH_MESH_GUNMAN,
	PATH_ANIM_GUNMAN,
	PATH_BB_NORMAL_MONSTER,
	PATH_BT_NORMAL_MONSTER,
	PATH_BB_TEST_MONSTER,
	PATH_BT_TEST_MONSTER,
	PATH_DATA_CHARACTER_TABLE,
	PATH_DATA_SKILL_TABLE,
	PATH_DATA_MONSTERSTAT_TABLE,
	PATH_DATA_CHARACTER_STAT_TABLE,
	PATH_DIR_SKILL_DATA,
	COUNT = PATH_DIR_SKILL_DATA
};
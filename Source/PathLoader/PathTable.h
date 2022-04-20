// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PathLoader.h"


#define CONVERT_TEXT	PathTable::GetInstance().GetAt
/**
 * 
 */

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

#define STRINGIFY(value) #value

inline bool IsEnabledActor(AActor* actor) {
	if (actor == nullptr) {
		return false;
	}

	USceneComponent* rootComponent = actor->GetRootComponent();
	if (rootComponent == nullptr) {
		return false;
	}

	return rootComponent->IsVisible();
}

inline void EnableActor(AActor* actor, bool enable) {
	if (actor == nullptr) {
		return;
	}

	USceneComponent* rootComponent = actor->GetRootComponent();
	if (rootComponent == nullptr) {
		return;
	}

	actor->SetActorEnableCollision(enable);
	actor->SetActorTickEnabled(enable);
	rootComponent->SetVisibility(enable);
}

template<typename T>
constexpr inline uint8 EnumToNum(T value) {
	return static_cast<uint8>(value);
}

template<typename T>
constexpr inline T NumToEnum(uint8 value) {
	if (!StaticEnum<ESkillType>()->IsValidEnumValue(value)) {
		return T::Count;
	}

	return static_cast<T>(value);
}

template<typename T>
constexpr inline FString EnumToFStr(T value) {
	return StaticEnum<T>()->GetValueAsString(value);
}

template<typename T>
constexpr inline T FStrToEnum(const FString& value) {
	if (value.IsEmpty()) {
		return T::Count;
	}

	if (!StaticEnum<ESkillType>()->IsValidEnumName(*value)) {
		return T::Count;
	}

	return NumToEnum<T>(StaticEnum<T>()->GetIndexByName(*value));
}

inline FVector2D GetViewportSize() {
	FVector2D viewport = { 1, 1 };
	if (GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(viewport);
	}

	return viewport;
}

inline FVector2D GetViewportCenter() {
	FVector2D viewport = { 1, 1 };
	if (GEngine && GEngine->GameViewport) {
		GEngine->GameViewport->GetViewportSize(viewport);
	}

	return FVector2D(viewport.X / 2, viewport.Y / 2);
}

static class PATHLOADER_API PathTable
{
private:
	PathTable();
	~PathTable();

	PathTable(const PathTable&) = delete;
	PathTable& operator=(const PathTable&) = delete;

public:
	static PathTable& GetInstance() {
		static PathTable instance;
		return instance;
	}

public:
	bool IsLoaded() const;
	bool Reload();
	bool Load();
	void Unload();

	const wchar_t* GetAt(EStringKey key) const;

private:
	bool 					isLoaded;
	TArray<std::wstring> 	stringPool;
};


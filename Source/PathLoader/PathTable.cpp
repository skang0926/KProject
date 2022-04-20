// Fill out your copyright notice in the Description page of Project Settings.


#include "PathTable.h"

PathTable::PathTable()
	: isLoaded(false) {
	stringPool.Reserve(EnumToNum(EStringKey::COUNT));
}

PathTable::~PathTable() {

}

bool PathTable::IsLoaded() const {
	return isLoaded;
}

bool PathTable::Reload() {
	FString path = FPaths::LaunchDir() + "String.txt";

	std::wifstream file(*path);
	if (!file.is_open()) {
		return false;
	}

	std::wstring line;
	while (getline(file, line)) {
		stringPool.Add(line.substr(line.find_last_of('\t') + 1));
	}

	return true;
}

bool PathTable::Load() {
	if (isLoaded) {
		return true;
	}

	return Reload();
}

void PathTable::Unload() {
	isLoaded = false;
	stringPool.Empty();
}

const wchar_t* PathTable::GetAt(EStringKey key) const {
	if (EStringKey::NONE == key) {
		return nullptr;
	}

	int index = EnumToNum(key);
	if (stringPool.Num() <= index) {
		return nullptr;
	}

	return stringPool[index].c_str();
}
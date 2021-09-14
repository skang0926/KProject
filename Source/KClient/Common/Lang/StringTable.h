#pragma once

#include "../../KClient.h"

#define CONVERT_TEXT	StringTable::GetInstance().GetAt

class StringTable {
private:
	StringTable();
	~StringTable();

	StringTable(const StringTable&) = delete;
	StringTable& operator=(const StringTable&) = delete;

public:
	static StringTable& GetInstance() {
		static StringTable instance;
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
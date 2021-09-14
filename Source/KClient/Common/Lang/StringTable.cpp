#include "StringTable.h"

StringTable::StringTable()
	: isLoaded(false) {
	stringPool.Reserve( EnumToNum( EStringKey::COUNT ) );
}

StringTable::~StringTable() {
	
}

bool StringTable::IsLoaded() const {
	return isLoaded;
}

bool StringTable::Reload() {
	FString path = FPaths::GameSourceDir() + "KClient/Common/Lang/String.txt";
	std::wifstream file( *path );
	if ( !file.is_open() ) {
		return false;
	}

	std::wstring line;
	while ( getline( file, line ) ) {
		stringPool.Add( line.substr( line.find_last_of( '\t' ) + 1 ) );
	}

	return true;
}

bool StringTable::Load() {
	if ( isLoaded ) {
		return true;
	}

	return Reload();
}

void StringTable::Unload() {
	isLoaded = false;
	stringPool.Empty();
}

const wchar_t* StringTable::GetAt(EStringKey key) const {
	if ( EStringKey::NONE == key ) {
		return nullptr;
	}
	
	int index = EnumToNum( key );
	if ( stringPool.Num() <= index ) {
		return nullptr;
	}

	return stringPool[ index ].c_str();
}
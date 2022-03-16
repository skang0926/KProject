// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "UObject/NoExportTypes.h"
#include "MemoryManager.generated.h"

/**
 * 
 */

struct FNodeMemory64
{
	TCHAR buffer[32]; // 64byte
};

class MemoryPool
{
public:
	MemoryPool();
	~MemoryPool();
	void Initialize(int32 num);

	void* Alloc();
	void Free(void* memory);

private:
	FNodeMemory64* memoryPool;

	//Key : memory's index in memory pool, Value : arrIndex
	TMap<int32, int32> indexTable;
	TArray<int32> indexArray;
	int32 offset;
	int32 memoryPoolSize;
};


UCLASS()
class KCLIENT_API UMemoryManager : public UObject
{
	GENERATED_BODY()


public:
	UMemoryManager();
	void Initialize(int32 memoryPoolSize);

private:
	MemoryPool memoryPool;
};
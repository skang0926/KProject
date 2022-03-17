// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryManager.h"

UMemoryManager::UMemoryManager()
{

}

void UMemoryManager::Initialize(int32 memoryPoolSize)
{
	memoryPool.Initialize(memoryPoolSize);
}



/////////////////////////////////////////////////// MemoryPool Func


// memoryIndex = memory's index in memory pool
// arrIndex = indexArray's index
// indexTable's Key - Value is memoryIndex - arrIndex

// indexArray's value = memory's index = indexTable's Key
// indexTable's value = index array's index


MemoryPool::MemoryPool()
{

}

MemoryPool::~MemoryPool()
{
	UE_LOG(LogClass, Warning, TEXT("Destruction Test"));
	if (memoryPool != nullptr)
		delete[] memoryPool;
}

void MemoryPool::Initialize(int32 size)
{
	memoryPool = new FNodeMemory64[size];
	memoryPoolSize = size;
	for (int32 i = 0; i < size; ++i)
	{
		indexTable.Add(i, i);
		indexArray.Add(i);
	}
	offset = 0;
}


void* MemoryPool::Alloc()
{
	if (offset >= memoryPoolSize || offset < 0)
		return nullptr;

	int32 memoryIndex = indexArray[offset++];

	void* memory = reinterpret_cast<void*>(&memoryPool[memoryIndex]);
	return memory;
}

void MemoryPool::Free(void* memory)
{
	if (memory == nullptr || offset == 0) return;

	FNodeMemory64* memoryPtr = reinterpret_cast<FNodeMemory64*>(memory);
	int32 memoryIndex = memoryPtr - &memoryPool[0];

	if (memoryIndex >= memoryPoolSize && memoryIndex < 0)
		return;

	int32 arrIndex = indexTable[memoryIndex];


	//Array에서 메모리의 위치 변경
	--offset;
	int32 temp = indexArray[arrIndex];
	indexArray[arrIndex] = indexArray[offset];
	indexArray[offset] = temp;


	//IndexTable 값 변경
	indexTable[memoryIndex] = offset;
	indexTable[indexArray[arrIndex]] = arrIndex;

	return;
}

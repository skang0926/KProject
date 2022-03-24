// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"

/**
 * 
 */

 enum class EMemoryBlock : uint8
 {
 	NONE = 0,
 	BLOCK64,
 	BLOCK128,
 	BLOCK256
 };
 
 struct FMemoryBlock64
 {
 	uint8 buffer[64]; // 64byte
 };
 
 struct FMemoryBlock128
 {
 	uint8 buffer[128]; // 128byte
 };
 
 struct FMemoryBlock256
 {
 	uint8 buffer[256]; // 256byte
 };

template <typename T>
class KCLIENT_API MemoryPool
{
public:
	MemoryPool(int32 memoryPoolSize);
	~MemoryPool();

	void* Alloc();
	void Free(void* memory);

private:
	T* memoryPool = nullptr;

	TDoubleLinkedList<int32> availableMemoryList;
	int32 memoryPoolSize;
};



template <typename T>
MemoryPool<T>::MemoryPool(int32 memoryPoolSize)
{
	memoryPool = new T[memoryPoolSize];
	memoryPoolSize = memoryPoolSize;
	for (int32 i = 0; i < memoryPoolSize; ++i)
	{
		availableMemoryList.AddHead(i);
	}
}


template <typename T>
MemoryPool<T>::~MemoryPool()
{
	if (memoryPool != nullptr)
		delete[] memoryPool;
}

template <typename T>
void* MemoryPool<T>::Alloc()
{
	if (availableMemoryList.Num() == 0)
	{
		UE_LOG(KP, Error, TEXT("Memory pool is full "));
		return nullptr;
	}

	auto headNode = availableMemoryList.GetHead();
	int32 memoryIndex = headNode->GetValue();

	void* memory = reinterpret_cast<void*>(&memoryPool[memoryIndex]);
	availableMemoryList.RemoveNode(headNode);

	return memory;
}

template <typename T>
void MemoryPool<T>::Free(void* memory)
{
	T* memoryPtr = reinterpret_cast<T*>(memory);
	int32 memoryIndex = memoryPtr - &memoryPool[0];

	if (memoryIndex >= memoryPoolSize && memoryIndex < 0)
	{
		UE_LOG(KP, Error, TEXT("Invalid access to memory pool"))
		return;
	}
	availableMemoryList.AddHead(memoryIndex);
	return;
}

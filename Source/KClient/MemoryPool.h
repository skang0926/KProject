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
	MemoryPool(int32 size);
	~MemoryPool();

	void* Alloc(int32&& memorySize);
	void Free(void* memory);

private:
	uint8* pivot = nullptr;
	uint8* memoryPoolPtr = nullptr;
};

template <typename T>
MemoryPool<T>::MemoryPool(int32 memoryPoolSize)
{
	memoryPoolPtr = new uint8[sizeof(T) * memoryPoolSize];
	pivot = memoryPoolPtr;

	uint8** cur = reinterpret_cast<uint8**>(memoryPoolPtr);
	uint8* next = memoryPoolPtr;

	for (int32 i = 0; i < memoryPoolSize - 1; ++i)
	{
		next += sizeof(T);
		*cur = next;
		cur = reinterpret_cast<uint8**>(next);
	}

	*cur = nullptr;
}


template <typename T>
MemoryPool<T>::~MemoryPool()
{
	if (memoryPoolPtr != nullptr)
		delete[] memoryPoolPtr;
}

template <typename T>
void* MemoryPool<T>::Alloc(int32&& memorySize)
{
	if (memorySize > sizeof(T))
	{
		UE_LOG(KP, Error, TEXT("MemoryBlock's size exceeded"));
		return nullptr;
	}

	if (pivot == nullptr)
	{
		UE_LOG(KP, Error, TEXT("memory pool is full"));
		return nullptr;
	}

	uint8* memoryPtr = pivot;
	pivot = *reinterpret_cast<uint8**>(pivot);
	return reinterpret_cast<void*>(memoryPtr);
}

template <typename T>
void MemoryPool<T>::Free(void* memory)
{
	*reinterpret_cast<uint8**>(memory) = pivot;
	pivot = reinterpret_cast<uint8*>(memory);

	return;
}

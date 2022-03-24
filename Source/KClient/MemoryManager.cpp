// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryManager.h"

////////////////////////////////////////////////// MemoryPool Func


UMemoryManager::UMemoryManager()
{

}

void UMemoryManager::CreateMemoryPool(int32 memoryPoolSize, EMemoryBlock blockType)
{
	switch (blockType)
	{
	case EMemoryBlock::BLOCK64:
		if (memoryPool64 == nullptr)
			memoryPool64 = new MemoryPool<FMemoryBlock64>(memoryPoolSize);
		break;
	case EMemoryBlock::BLOCK128:
		if (memoryPool128 == nullptr)
			memoryPool128 = new MemoryPool<FMemoryBlock128>(memoryPoolSize);
		break;
	case EMemoryBlock::BLOCK256:
		if (memoryPool256 == nullptr)
			memoryPool256 = new MemoryPool<FMemoryBlock256>(memoryPoolSize);
		break;
	default:
		UE_LOG(KP, Error, TEXT("Non exist type"));
		break;
	}
}

void UMemoryManager::FreeMemoryPool()
{
	if(memoryPool64 != nullptr)
		delete memoryPool64;

	if (memoryPool128 != nullptr)
		delete memoryPool128;

	if (memoryPool256 != nullptr)
		delete memoryPool256;
}


MemoryPool<FMemoryBlock64>* UMemoryManager::GetMemoryPool64() const
{
	if (memoryPool64 == nullptr)
	{
		UE_LOG(KP, Error, TEXT("MemoryPool64 is non-existent"));
		return nullptr;
	}
	return memoryPool64;
}

MemoryPool<FMemoryBlock128>* UMemoryManager::GetMemoryPool128() const
{
	if (memoryPool128 == nullptr)
	{
		UE_LOG(KP, Error, TEXT("MemoryPool128 is non-existent"));
		return nullptr;
	}
	return memoryPool128;
}

MemoryPool<FMemoryBlock256>* UMemoryManager::GetMemoryPool256() const
{
	if (memoryPool256 == nullptr)
	{
		UE_LOG(KP, Error, TEXT("MemoryPool256 is non-existent"));
		return nullptr;
	}
	return memoryPool256;
}


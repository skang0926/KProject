// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "UObject/NoExportTypes.h"
#include "MemoryPool.h"
#include "MemoryManager.generated.h"


UCLASS()
class KCLIENT_API UMemoryManager : public UObject
{
	GENERATED_BODY()


public:
	UMemoryManager();
	void CreateMemoryPool(int32 memoryPoolSize, EMemoryBlock blockType);
	void FreeMemoryPool();

	MemoryPool<FMemoryBlock64>* GetMemoryPool64() const;
	MemoryPool<FMemoryBlock128>* GetMemoryPool128() const;
	MemoryPool<FMemoryBlock256>* GetMemoryPool256() const;

private:
	MemoryPool<FMemoryBlock64>* memoryPool64 = nullptr;
	MemoryPool<FMemoryBlock128>* memoryPool128 = nullptr;
	MemoryPool<FMemoryBlock256>* memoryPool256 = nullptr;
};
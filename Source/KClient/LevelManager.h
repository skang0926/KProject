// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "GameFramework/Actor.h"
#include "MemoryManager.h"
#include "LevelManager.generated.h"

UCLASS()
class KCLIENT_API ALevelManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	class UMemoryManager* GetMemoryManager() const;

private:
	void SpawnMonster();
private:

	UPROPERTY()
	UMemoryManager* memoryManager;


	//메모리 풀 테스트 코드
	UPROPERTY(EditAnywhere)
	int32 monsterMax;

	UPROPERTY(EditAnywhere)
		bool bMemoryPoolTest;

	int32 monsterNum;
	FTimerHandle timer;
};

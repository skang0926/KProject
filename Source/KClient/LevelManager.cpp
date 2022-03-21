// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "MemoryManager.h"
#include "TestMonster.h"
#include "KProjectGameInstance.h"

// Sets default values
ALevelManager::ALevelManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	monsterMax = 300;
	monsterNum = 0;
}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();
	
	memoryManager = NewObject<UMemoryManager>(this);
	memoryManager->Initialize(monsterMax);

	// 메모리풀 테스트 코드

	GAME_INSTANCE()->SetLevelManager(this);

	GetWorldTimerManager().SetTimer(timer, this, &ALevelManager::SpawnMonster, 1.f, true, 0.1f);
}

void ALevelManager::SpawnMonster()
{
	// 메모리풀 테스트 코드

	if (monsterNum >= monsterMax)
	{
		GetWorldTimerManager().ClearTimer(timer);
		return;
	}

	for (int i = 0; i < 10; ++i)
	{
		auto monster = GetWorld()->SpawnActor<ATestMonster>(ATestMonster::StaticClass(), FVector(-60.f - i * 300, -1080.f, 500.f), FRotator::ZeroRotator);
		monster->Initialize(FName(TEXT("TestMonster")));

	}

	monsterNum += 10;
	UE_LOG(LogClass, Warning, TEXT("Monster Num : %d"), monsterNum)
}

UMemoryManager* ALevelManager::GetMemoryManager() const
{
	return memoryManager;
}

// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


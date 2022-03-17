// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "GameFramework/Actor.h"
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void GetMemoryManager() const;

private:
	void SpawnMonster();
private:
	class UMemoryManager* memoryManager;


	//�޸� Ǯ �׽�Ʈ �ڵ�
	UPROPERTY(EditAnywhere)
	int32 monsterMax;

	int32 monsterNum;
	FTimerHandle timer;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "KClient.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "MonsterStatComponent.generated.h"


UENUM()
enum class EMonsterTendency
{
	Aggressive,
	Defensive
};

USTRUCT(BlueprintType)
struct FMonsterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FMonsterStat() {};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 Hp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	EMonsterTendency Tendency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stat")
	float MoveSpeed;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KCLIENT_API UMonsterStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMonsterStatComponent();

	void Initialize(FName monsterName);
	const FMonsterStat& GetMonsterStat() { return monsterStat; }
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere)
	FMonsterStat monsterStat;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "MonsterBase.h"
#include "SkillSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterDataTable.h"
#include "Engine/DataTable.h"
#include "MonsterStatComponent.h"
#include "LockOnComponent.h"
#include "DamageableComponent.h"
#include "MonsterAIController.h"

AMonsterBase::AMonsterBase()
{
	lockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));
	monsterStatComponent = CreateDefaultSubobject<UMonsterStatComponent>(TEXT("Stat"));

	characterName = TEXT("Gunman");
	bAllowInitialize = false;
	AutoPossessAI = EAutoPossessAI::Disabled;
}


void AMonsterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

void AMonsterBase::UseSkill(ESkillType skillType)
{
	// if (isAttacking) return; // 아직 캐릭터 상태 FSM 없어서 사용 불가능.
	GetSkillSystem()->UseActiveSkill(skillType);

	OnAttackDelegate.Broadcast();
	isAttacking = true;
}

void AMonsterBase::BeginPlay()
{
	if (!bAllowInitialize) return;

	Super::BeginPlay();
	monsterStatComponent->Initialize(characterName);
	GetCharacterMovement()->MaxWalkSpeed = monsterStatComponent->GetMonsterStat().MoveSpeed;
	damageableComponent->Init(monsterStatComponent->GetMonsterStat().Hp, 100);
	AIControllerClass = AMonsterAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	SpawnDefaultController();
}

void AMonsterBase::Initialize(const FName name)
{
	characterName = name;
	bAllowInitialize = true;
	BeginPlay();
}

int32 AMonsterBase::GetBaseDamage() const
{
	if (!monsterStatComponent) {
		return 0;
	}

	return monsterStatComponent->GetMonsterStat().Damage;
}

void AMonsterBase::SetLockOnComponent(ACharacterBase* otherCharacter)
{
	lockOnComponent->SetTargetCharacter(otherCharacter);
}
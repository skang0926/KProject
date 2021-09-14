#include "SkillSystem.h"
#include "ActiveSkill.h"
#include "PassiveSkill.h"

USkillSystem::USkillSystem() {
	PrimaryComponentTick.bCanEverTick = false;
}

USkillBase* USkillSystem::Factory( ESkillType type ) {
	ACharacterBase* const owner = GetOwner<ACharacterBase>();
	if ( owner == nullptr ) {
		return nullptr;
	}

	UClass* skillClass = nullptr;
	switch (type) {
	case ESkillType::HitScanShot:
		skillClass = UHitScanShotSkill::StaticClass();
		break;
	case ESkillType::CircularSectorShot:
		skillClass = UCircularSectorShotSkill::StaticClass();
		break;
	default:
		return nullptr;
	}
	
	auto skillProperty = GAME_INSTANCE()->GetSkillTableRow( *skillClass->GetName() );
	if ( skillProperty == nullptr ) {
		return nullptr;
	}

	USkillBase* newSkill = NewObject<USkillBase>( owner, skillClass, *skillClass->GetName() );
	newSkill->RegisterComponent();
	newSkill->Initialize(skillProperty);
	return newSkill;
}

void USkillSystem::RegisterSkill( ESkillType type ) {
	if ( skillTable.Contains( type ) ) {
		return;
	}

	USkillBase* newSkill = Factory( type );
	if (!newSkill) {
		UE_LOG( KP, Error, TEXT("couldn't register skill %d"),  );
		return;
	}

	skillTable.Add( type, newSkill );
}

void USkillSystem::UnregisterSkill( ESkillType type ) {
	if ( !skillTable.Contains( type ) ) {
		return;
	}

	skillTable.FindRef( type )->DestroyComponent();
	skillTable.Remove( type );
}

void USkillSystem::Clear() {
	skillTable.Empty();
}

void USkillSystem::UseActiveSkill( ESkillType type ) {
	if ( !skillTable.Contains( type ) ) {
		return;
	}

	USkillBase* skill = skillTable.FindRef( type );
	if ( !skill->IsActiveType() ) {
		return;
	}

	if (skill->IsRemainCooldown()) {
		return;
	}
		
	skill->Use();
}

USkillBase* USkillSystem::GetSkill( ESkillType type ) {
	if ( !skillTable.Contains( type ) ) {
		return nullptr;
	}

	return skillTable.FindRef( type );
}
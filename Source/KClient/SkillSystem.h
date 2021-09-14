#pragma once

#include "KClient.h"
#include "SkillSystem.generated.h"

class ACharacterBase;
class USkillBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KCLIENT_API USkillSystem : public UActorComponent {
	GENERATED_BODY()

public:
	USkillSystem();

	void RegisterSkill( ESkillType type );
	void UnregisterSkill( ESkillType type );
	void Clear();

	void UseActiveSkill( ESkillType type );

	USkillBase* GetSkill( ESkillType type );

private:
	USkillBase* Factory( ESkillType type );

private:
	UPROPERTY(VisibleAnywhere)
	TMap<ESkillType, USkillBase*>	skillTable;
};
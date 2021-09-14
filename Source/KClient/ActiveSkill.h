#pragma once

#include "KClient.h"
#include "ActiveSkill.generated.h"

UCLASS()
class KCLIENT_API UCircularSectorShotSkill : public USkillBase {
	GENERATED_BODY()

public:	
	virtual void Use() override;
};

UCLASS()
class KCLIENT_API UHitScanShotSkill : public USkillBase {
	GENERATED_BODY()

public:	
	virtual void Use() override;
};
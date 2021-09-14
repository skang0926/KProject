#pragma once

#include "KClient.h"
#include "BasicType.h"
#include "SkillBase.generated.h"

USTRUCT(BlueprintType)
struct FSkillProperty : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32				skillID;			// skill 대역 확인용

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				curLevel;			// 스킬 현재 레벨

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				reqLevel;			// 스킬 요구 레벨

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				maxLevel;			// 스킬 최대 레벨

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString				description;		// 스킬 설명

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32				damagePercentRate;	// 기본 공격력을 베이스로 하는 데미지 퍼센티지

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				attackCount;		// 히트 횟수

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float				cooldown;			// 쿨타임

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool				isActiveType;		// 액티브형 스킬인가?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool				isInstallType;		// 설치형 스킬인가?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESkillType			skillType;			// 스킬 타입

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EAttackType			attackType;			// ex) 단일, 다단히트, 폭발, 다수 공격 등
};

UCLASS(Abstract)
class KCLIENT_API USkillBase : public UActorComponent {
	GENERATED_BODY()

public:
	USkillBase();

	virtual void		TickComponent(float deltaTime, ELevelTick tickType, FActorComponentTickFunction* thisTickFunction) override;

	virtual void		Initialize( const FSkillProperty* initProperty );
	virtual void		Use();

	FSkillProperty&		GetCommonProperty();
	bool				IsActiveType() const;
	bool				IsInstallType() const;
	bool				IsRemainCooldown() const;
	double				GetCooldownRemaining() const;

protected:
	double				lastUpdatedTime;
	FSkillProperty		commonProperty;
	UDataAsset* 		uniqueProperty;
};
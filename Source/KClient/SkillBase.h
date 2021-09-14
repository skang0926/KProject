#pragma once

#include "KClient.h"
#include "BasicType.h"
#include "SkillBase.generated.h"

USTRUCT(BlueprintType)
struct FSkillProperty : public FTableRowBase {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32				skillID;			// skill �뿪 Ȯ�ο�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				curLevel;			// ��ų ���� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				reqLevel;			// ��ų �䱸 ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				maxLevel;			// ��ų �ִ� ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		FString				description;		// ��ų ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32				damagePercentRate;	// �⺻ ���ݷ��� ���̽��� �ϴ� ������ �ۼ�Ƽ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		uint8				attackCount;		// ��Ʈ Ƚ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		float				cooldown;			// ��Ÿ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool				isActiveType;		// ��Ƽ���� ��ų�ΰ�?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool				isInstallType;		// ��ġ�� ��ų�ΰ�?

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ESkillType			skillType;			// ��ų Ÿ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		EAttackType			attackType;			// ex) ����, �ٴ���Ʈ, ����, �ټ� ���� ��
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